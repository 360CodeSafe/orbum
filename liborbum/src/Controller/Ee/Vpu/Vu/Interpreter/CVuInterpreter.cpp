#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"

#include "Core.hpp"
#include "Resources/RResources.hpp"

CVuInterpreter::CVuInterpreter(Core* core) :
    CController(core)
{
}

void CVuInterpreter::handle_event(const ControllerEvent& event)
{
    switch (event.type)
    {
    case ControllerEvent::Type::Time:
    {
        int ticks_remaining = time_to_ticks(event.data.time_us);
        while (ticks_remaining > 0)
            ticks_remaining -= time_step(ticks_remaining);
        break;
    }
    default:
    {
        throw std::runtime_error("CVuInterpreter event handler not implemented - please fix!");
    }
    }
}

int CVuInterpreter::time_to_ticks(const double time_us)
{
    int ticks = static_cast<int>(time_us / 1.0e6 * Constants::EE::VPU::VU::VU_CLK_SPEED * core->get_options().system_bias_vu);

    if (ticks < 10)
    {
        static bool warned = false;
        if (!warned)
        {
            BOOST_LOG(Core::get_logger()) << "Vu ticks too low - increase time delta";
            warned = true;
        }
    }

    return ticks;
}

int CVuInterpreter::time_step(const int ticks_available)
{
    // TODO: Not yet implemented.
#if defined(BUILD_DEBUG)
    DEBUG_LOOP_COUNTER++;
#endif
    return 1;
}
