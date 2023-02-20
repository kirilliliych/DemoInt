#ifndef GRAPH_DRAWER_HPP
#define GRAPH_DRAWER_HPP


#include <iostream>
#include "demoint.hpp"
#include "location.hpp"


static const char *DEFAULT_GRAPH_SOURCE_FILE_NAME  = "tracked_graph.txt";
static const char *DEFAULT_GRAPH_PICTURE_FILE_NAME = "tracking_picture.png";


static const char *FUNCTIONS_DARKENING_BACKGROUND = "#00000020";
static const char *OP_NODE_COLOR                  = "#340570ff";
static const char *OP_NODE_FILL_COLOR             = "#9a6ad6ff";
static const char *EXPLICIT_VARIABLE_FILL_COLOR   = "#34c6cdff";
static const char *EXPLICIT_VARIABLE_COLOR        = "#006064ff";
static const char *TEMP_VARIABLE_NODE_COLOR       = "#a62000ff";
static const char *TEMP_VARIABLE_NODE_FILL_COLOR  = "#fb3f51ff";

static const char *DEFAULT_EDGE_COLOR             = "#ffaa00ff";
static const char *DEFAULT_EDGE_LABEL_COLOR       = "#000000ff";
static const char *COPY_EDGE_COLOR                = "#ff0000ff";
static const char *COPY_EDGE_LABEL_COLOR          = COPY_EDGE_COLOR;
static const char *MOVE_EDGE_COLOR                = "#0acf00ff";
static const char *MOVE_EDGE_LABEL_COLOR          = MOVE_EDGE_COLOR;


class DemoInt;

struct OpNode
{
    const char *op_symb     = "";
    size_t op_identificator = 0; 
};

class GraphDrawer
{
public:
//---------------------------------------------------------------------------------------
    GraphDrawer(const char *graph_source_file_name  = DEFAULT_GRAPH_SOURCE_FILE_NAME,
                const char *graph_picture_name      = DEFAULT_GRAPH_PICTURE_FILE_NAME);

    GraphDrawer(const GraphDrawer &)             = delete;
    GraphDrawer &operator =(const GraphDrawer &) = delete;

    ~GraphDrawer();
//---------------------------------------------------------------------------------------
    void create_var_node(const DemoInt &var, const char *color, const char *fillcolor) const;

    OpNode create_op_node(const char *op_symb_str, const char *color, const char *fillcolor) const;

    void create_edge(const DemoInt &from, const OpNode &to, const char *color,
                     const char *label, const char *label_color) const;

    void create_edge(const OpNode &from, const DemoInt &to, const char *color,
                     const char *label, const char *label_color) const;

    void create_edge(const DemoInt &from, const DemoInt &to, const char *color,
                     const char *label, const char *label_color) const;

    void enter_cluster(Location location) const;

    void exit_cluster() const;
//--------------------Variables----------------------------------------------------------
    static GraphDrawer *GRAPH_DRAWER_SINGLETON;

private:

    static size_t op_counter_;
    static size_t cluster_counter_;

    FILE *graph_source_file_        = nullptr;
    std::string graph_picture_name_ = "";
};

#endif
