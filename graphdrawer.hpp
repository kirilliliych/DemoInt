#ifndef GRAPH_DRAWER_HPP
#define GRAPH_DRAWER_HPP


#include <iostream>
#include "demoint.hpp"


static std::string DEFAULT_GRAPH_SOURCE_FILE_NAME  = "tracked_graph.txt";
static std::string DEFAULT_GRAPH_PICTURE_FILE_NAME = "tracking_picture.png"; 


class DemoInt;

struct OpNode
{
    const char *op_symb     = "";
    size_t op_identificator = 0; 
};

class GraphDrawer
{
public:
//----------------------------------------------------
    GraphDrawer(std::string &graph_source_file_name  = DEFAULT_GRAPH_SOURCE_FILE_NAME,
                std::string &graph_picture_name      = DEFAULT_GRAPH_PICTURE_FILE_NAME);

    ~GraphDrawer();
//----------------------------------------------------
    void create_var_node(const DemoInt &var, const char *color) const;

    OpNode create_op_node(const char *op_symb_str, const char *color) const;

    void create_edge(const DemoInt &from, const OpNode &to, const char *color,
                     const char *label, const char *label_color) const;
                     
    void create_edge(const OpNode &from, const DemoInt &to, const char *color,
                     const char *label, const char *label_color) const;
//--------------------Variables-----------------------
private:

    static size_t op_counter_;

    FILE *graph_source_file_        = nullptr;
    std::string graph_picture_name_ = "";
};


#endif