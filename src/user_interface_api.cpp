#include "user_interface_api.hpp"
#include "agent.hpp"
#include "dijkstra.hpp"

UserInterfaceAPI::UserInterfaceAPI():
    grid(5,5,0,0,4,4)
{
    agents = std::vector<Agent>();
}

void UserInterfaceAPI::changeGrid(int width, int height,
                                    int start_x, int start_y,
                                        int end_x, int end_y){
    grid.~Grid();
    new (&grid) Grid(width, height, start_x, start_y, end_x, end_y);
}

void UserInterfaceAPI::addAgent(AgentID id){
	switch(id){
        case AgentID::DIJKSTRA:
            Dijkstra new_agent;
            agents.push_back(new_agent);
            break;
	}
}


