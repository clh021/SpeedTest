//
// Created by Francesco Laurita on 9/9/16.
//

#ifndef SPEEDTEST_CMDOPTIONS_H
#define SPEEDTEST_CMDOPTIONS_H
#include <getopt.h>

enum OutputType { verbose, text, json };


typedef struct program_options_t {
    bool help     = false;
    bool latency  = false;
    bool download = false;
    bool upload   = false;
    bool share    = false;
    bool insecure = false;
    std::string selected_server = "";
    OutputType output_type = OutputType::verbose;
} ProgramOptions;

static struct option CmdLongOptions[] = {
        {"help",        no_argument,       0, 'h' },
        {"latency",     no_argument,       0, 'l' },
        {"download",    no_argument,       0, 'd' },
        {"upload",      no_argument,       0, 'u' },
        {"share",       no_argument,       0, 's' },
        {"insecure",    no_argument,       0, 'i' },
        {"test-server", required_argument, 0, 't' },
        {"output",      required_argument, 0, 'o' },
        {0,             0,                 0,  0  }
};

const char *optStr = "hldusiqt:o:";

bool ParseOptions(const int argc, const char **argv, ProgramOptions& options){
    int long_index =0;
    int opt = 0;

    // 支持从环境变量指定 测试服务器
    options.selected_server.append(getenv("NET_TEST_SERVER"));

    while ((opt = getopt_long(argc, (char **)argv, optStr, CmdLongOptions, &long_index )) != -1) {
        switch (opt){
            case 'h':
                options.help     = true;
                break;
            case 'l':
                options.latency  = true;
                break;
            case 'd':
                options.download = true;
                break;
            case 'u':
                options.upload   = true;
                break;
            case 's':
                options.share    = true;
                break;
            case 'i':
                options.insecure = true;
                break;
            case 't':
                options.selected_server.append(optarg);
                break;
            case 'o':
                if (strcmp(optarg, "verbose") == 0)
                    options.output_type = OutputType::verbose;
                else if (strcmp(optarg, "text") == 0)
                    options.output_type = OutputType::text;
                else if (strcmp(optarg, "json") == 0)
                    options.output_type = OutputType::json;
                else {
                    std::cerr << "Unsupported output type " << optarg << std::endl;
                    std::cerr << "Supported output type: default, text, json" <<std::endl;
                    return false;
                }

                break;
            default:
                return false;
        }

    }
    return true;
}


#endif //SPEEDTEST_CMDOPTIONS_H
