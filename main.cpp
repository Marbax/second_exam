#include "Game.h"
using namespace sf;

int main()
{
    Game game;

    try
    {
        game.run();
    }
    catch (const std::invalid_argument &ex)
    {
        std::cerr << "Error : " << ex.what() << std::endl;
    }
    catch (const std::out_of_range &ex)
    {
        std::cerr << "Error : " << ex.what() << std::endl;
    }
    catch (const std::logic_error &ex)
    {
        std::cerr << "Error. " << ex.what() << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error : " << ex.what() << std::endl;
    }

    std::cout << "\nEND OF PROGRAM!" << std::endl;
    return 0;
}
