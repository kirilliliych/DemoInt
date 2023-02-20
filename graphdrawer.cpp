#include "graphdrawer.hpp"


GraphDrawer *GraphDrawer::GRAPH_DRAWER_SINGLETON = nullptr;

size_t GraphDrawer::copy_ctor_counter_       = 0;
size_t GraphDrawer::copy_assignment_counter_ = 0;
size_t GraphDrawer::move_ctor_counter_       = 0;
size_t GraphDrawer::move_assignment_counter_ = 0;

size_t GraphDrawer::op_counter_      = 0;
size_t GraphDrawer::cluster_counter_ = 0;


const char *VAR_NODE_MARK = "var_node";
const char *OP_NODE_MARK  = "op_node";


GraphDrawer::GraphDrawer(const char *graph_source_file_name, const char *graph_picture_name)
  : graph_source_file_(fopen(graph_source_file_name, "w")),
    graph_picture_name_(graph_picture_name)
{
    assert(graph_source_file_name);
    assert(graph_picture_name);

    GRAPH_DRAWER_SINGLETON = this;

    fprintf(graph_source_file_, "digraph G  \n"
                                "{          \n"
                                "rankdir=TB;\n");
}

GraphDrawer::~GraphDrawer()
{
    fprintf(graph_source_file_, "subgraph brief_info\n"
                                "{                  \n"
                                "rankdir=TB;"
                                "COPY_CTORS[style=filled, fillcolor=\"%s\", shape=diamond, label=\"COPY_CTORS=%lu\"];\n"
                                "COPY_ASSIGNMENTS[style=filled, fillcolor=\"%s\", shape=diamond, label=\"COPY_ASSIGNMENTS=%lu\"];\n"
                                "MOVE_CTORS[style=filled, fillcolor=\"%s\", shape=diamond, label=\"MOVE_CTORS=%lu\"];\n"
                                "MOVE_ASSIGNMENTS[style=filled, fillcolor=\"%s\", shape=diamond, label=\"MOVE_ASSIGNMENTS=%lu\"];\n"
                                "TEMP_VARIABLES[style=filled, fillcolor=\"%s\", shape=diamond, label=\"=TEMP_VARIABLES=%lu\"];\n"
                                "}\n",
                                COPY_EDGE_COLOR,                   
                                GraphDrawer::copy_ctor_counter_,
                                COPY_ASSIGNMENT_EDGE_COLOR,
                                GraphDrawer::copy_assignment_counter_,
                                MOVE_EDGE_COLOR,
                                GraphDrawer::move_ctor_counter_,
                                MOVE_ASSIGNMENT_EDGE_COLOR,
                                GraphDrawer::move_assignment_counter_,
                                TEMP_VARIABLE_NODE_FILL_COLOR,
                                DemoInt::get_temp_counter());

    fprintf(graph_source_file_, "}\n");

    fclose(graph_source_file_);
    graph_source_file_ = nullptr;

    char system_str[64] = {0};
    sprintf(system_str, "dot -Tpng %s -o %s", DEFAULT_GRAPH_SOURCE_FILE_NAME, DEFAULT_GRAPH_PICTURE_FILE_NAME);
    system(system_str);
}


void GraphDrawer::create_var_node(const DemoInt &var, const char *color, const char *fillcolor) const
{
    assert(color              != nullptr);
    assert(fillcolor          != nullptr);
    assert(graph_source_file_ != nullptr);
    
    fprintf(graph_source_file_, "%s%p%s[style=filled, fillcolor=\"%s\", color=\"%s\", shape=record,"
                                       "label=\"name \\n '%s' | value \\n %d | addr \\n %p\"];\n", 
                                VAR_NODE_MARK,
                                static_cast<const char *> (var.get_address()),
                                var.get_name().c_str(),
                                fillcolor,
                                color,
                                var.get_name().c_str(),
                                var.get_value(),
                                var.get_address());
}

OpNode GraphDrawer::create_op_node(const char *op_symb_str, const char *color, const char *fillcolor) const
{
    assert(op_symb_str        != nullptr);
    assert(color              != nullptr);
    assert(fillcolor          != nullptr);
    assert(graph_source_file_ != nullptr);

    fprintf(graph_source_file_, "%s%lu[style=filled, fillcolor=\"%s\", color=\"%s\","
                                      "shape=oval, label=\"%s\"];\n", 
                                 OP_NODE_MARK, op_counter_, fillcolor, color, op_symb_str);
    
    OpNode op_node = {op_symb_str, op_counter_};

    ++op_counter_;

    return op_node;
}


void GraphDrawer::create_edge(const DemoInt &from, const OpNode &to, const char *color,
                              const char *label, const char *label_color) const
{
    assert(color              != nullptr);
    assert(label              != nullptr);
    assert(label_color        != nullptr);
    assert(graph_source_file_ != nullptr);

    fprintf(graph_source_file_, "%s%p%s->%s%s[color=\"%s\", label=\"%s\", fontcolor=\"%s\"];\n",
                                VAR_NODE_MARK,
                                static_cast<const char *> (from.get_address()),
                                from.get_name().c_str(),
                                OP_NODE_MARK,
                                std::to_string(static_cast<int> (to.op_identificator)).c_str(),
                                color,
                                label,
                                label_color);
}

void GraphDrawer::create_edge(const OpNode &from, const DemoInt &to, const char *color,
                              const char *label, const char *label_color) const
{
    assert(color              != nullptr);
    assert(label              != nullptr);
    assert(label_color        != nullptr);
    assert(graph_source_file_ != nullptr);

    fprintf(graph_source_file_, "%s%s->%s%p%s[color=\"%s\", label=\"%s\", fontcolor=\"%s\"];\n",
                                OP_NODE_MARK,
                                std::to_string(static_cast<int> (from.op_identificator)).c_str(),
                                VAR_NODE_MARK,
                                static_cast<const char *> (to.get_address()),
                                to.get_name().c_str(),
                                color,
                                label,
                                label_color);
}

void GraphDrawer::create_edge(const DemoInt &from, const DemoInt &to, const char *color,
                              const char *label, const char *label_color) const
{
    assert(color              != nullptr);
    assert(label              != nullptr);
    assert(label_color        != nullptr);
    assert(graph_source_file_ != nullptr);

    fprintf(graph_source_file_, "%s%p%s->%s%p%s[color=\"%s\", label=\"%s\", fontcolor=\"%s\"];\n",
                                VAR_NODE_MARK,
                                static_cast<const char *> (from.get_address()),
                                from.get_name().c_str(),
                                VAR_NODE_MARK,
                                static_cast<const char *> (to.get_address()),
                                to.get_name().c_str(),
                                color,
                                label,
                                label_color);
}

void GraphDrawer::enter_cluster(Location location) const
{
    fprintf(graph_source_file_, "subgraph cluster_%lu {\n"
                                "style=filled;\n"
                                "fillcolor=\"%s\";\n"
                                "label=\"FILE %s FUNC %s LINE %d\";\n",
                                cluster_counter_,
                                FUNCTIONS_DARKENING_BACKGROUND,
                                location.file_,
                                location.func_,
                                location.line_);
    ++cluster_counter_;
}

void GraphDrawer::exit_cluster() const
{
    fprintf(graph_source_file_, "}\n");
}


void GraphDrawer::inc_copy_ctor_counter()
{
    ++copy_ctor_counter_;
}

void GraphDrawer::inc_copy_assignment_counter()
{
    ++copy_assignment_counter_;
}

void GraphDrawer::inc_move_ctor_counter()
{
    ++move_ctor_counter_;
}

void GraphDrawer::inc_move_assignment_counter()
{
    ++move_assignment_counter_;
}
