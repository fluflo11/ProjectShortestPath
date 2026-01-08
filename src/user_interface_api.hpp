#ifndef USER_INTERFACE_API_HPP
#define USER_INTERFACE_API_HPP

#include "grid.hpp"
#include "agent.hpp"
#include <vector>
#include <iostream>

class UserInterfaceAPI{

private: 
    Grid grid;
    std::vector<Agent> agents;    

public:
    /**
     * To change grid dimentions
    */
    void changeGrid(int width, int height, 
                        int start_x, int start_y,
                            int end_x, int end_y);
    /**
     * Add a new pathfinder agent
     */
    void addAgent(AgentID id);

    UserInterfaceAPI();

};

#endif