#include "graphdrawer.hpp"


size_t GraphDrawer::op_counter_      = 0;
size_t GraphDrawer::cluster_counter_ = 0;


const char *VAR_NODE_MARK = "var_node";
const char *OP_NODE_MARK  = "op_node";


GraphDrawer::GraphDrawer(std::string &graph_source_file_name, std::string &graph_picture_name)
  : graph_source_file_(fopen(graph_source_file_name.c_str(), "w")),
    graph_picture_name_(graph_picture_name)
{
    fprintf(graph_source_file_, "digraph G\n"
                                "{   \n"
                                "rankdir=\"TB\"\n");
}

GraphDrawer::~GraphDrawer()
{
    fprintf(graph_source_file_, "}");

    fclose(graph_source_file_);
    graph_source_file_ = nullptr;
}


void GraphDrawer::create_var_node(const DemoInt &var, const char *color) const
{
    assert(color              != nullptr);
    assert(graph_source_file_ != nullptr);
    
    fprintf(graph_source_file_, "%s%p%s[color=%s, shape=record, label=\"name \\n '%s' | value \\n %d | addr \\n %p \"];\n",
                                VAR_NODE_MARK,
                                static_cast<const char *> (var.get_address()),
                                var.get_name().c_str(),
                                color,
                                var.get_name().c_str(),
                                var.get_value(),
                                var.get_address());
}

OpNode GraphDrawer::create_op_node(const char *op_symb_str, const char *color) const
{
    assert(op_symb_str        != nullptr);
    assert(graph_source_file_ != nullptr);

    fprintf(graph_source_file_, "%s%lu[color=%s, shape=oval, label=\" %s \"];\n", 
                                OP_NODE_MARK, op_counter_, color, op_symb_str);
    
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

    fprintf(graph_source_file_, "%s%p%s->%s%s[color=%s, label=\"%s\", fontcolor=\"%s\"];\n",
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

    fprintf(graph_source_file_, "%s%s->%s%p%s[color=%s, label=\"%s\", fontcolor=\"%s\"];\n",
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

    fprintf(graph_source_file_, "%s%p%s->%s%p%s[color=%s, label=\"%s\", fontcolor=\"%s\"];\n",
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

void GraphDrawer::enter_cluster(std::experimental::source_location location) const
{
    fprintf(graph_source_file_, "subgraph cluster_%lu {\n"
                                "label=\"FILE %s FUNC %s LINE %d\";\n",
                                cluster_counter_,
                                location.file_name(),
                                location.function_name(),
                                location.line());
    ++cluster_counter_;
}

void GraphDrawer::exit_cluster() const
{
    fprintf(graph_source_file_, "}\n");
}
