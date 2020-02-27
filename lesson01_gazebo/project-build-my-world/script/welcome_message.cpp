#include <iostream>
#include <gazebo/gazebo.hh>

namespace gazebo
{

class WorldPluginWelcomeMessage : public WorldPlugin
{
    public:
    WorldPluginWelcomeMessage() : WorldPlugin()
    {
        std::cout << "Welcome to William's World!" << std::endl;
    }

    void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
    {
    }
};

GZ_REGISTER_WORLD_PLUGIN(WorldPluginWelcomeMessage);
}
