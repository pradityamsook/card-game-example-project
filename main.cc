#include <drogon/drogon.h>
#include <locale>

int main()
{
    // try
    // {
    //     std::locale::global(std::locale("en_US"));
    // }
    // catch (const std::runtime_error &e)
    // {
    //     std::cerr << "Error setting locale: " << e.what() << std::endl;
    //     return 1;
    // }

    // Set HTTP listener address and port
    //  drogon::app().addListener("0.0.0.0", 8081).run();
    std::cout << "Server running...\n";
    std::cout << "run at port 8088\n";
    // Load config file
    drogon::app().loadConfigFile("../config.json").run();
    // LOG_INFO << "Database config loaded: " << drogon::app().getDbClientManager().getAllDbClients().size();
    
    return 0;
}