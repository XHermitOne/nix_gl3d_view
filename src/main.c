/**
* Модуль функции MAIN
* @author XHermit <xhermitone@gmail.com>
* @file
* @version 0.0.0.1
*/

#include "main.h"

/**
* Режим отладки
*/
BOOL DebugMode = TRUE;

/**
* Основная функция MAIN. Анализ параметров коммандной строки и 
* установка этих параметров. 
*
* Параметры коммандной строки:
* @param \--help|-h|-? Напечатать строки помощи
* @param \--version|-v  Напечатать версию программы
* @param \--debug|-D Включить режим отладки
* @param \--log|-L Включить режим журналирования
*/

int main (int argc, char **argv)
{
    int result = 0;
    
    open_log(NULL);
    
    if (check_parameters("--help", argc, argv) || check_parameters("-h", argc, argv) || check_parameters("-?", argc, argv))
    {
        print_help();
        return 0;
    }

    if (check_parameters("--version", argc, argv) || check_parameters("-v", argc, argv))
    {
        print_version ();
        return 0;
    }

    if ((check_parameters("--debug", argc, argv) || check_parameters("-D", argc, argv)) || (check_parameters("--log", argc, argv) || check_parameters("-L", argc, argv)))
        DebugMode = TRUE;
    else
        DebugMode = FALSE;

    result = run(argc, argv);

    close_log();
    
    return result;
}


/**
* Функция запуска основного алгоритма
*/
int run(int argc, char *argv[])
{
    // Разбор коммандной строки
    int opt = 0;
    // BOOL is_select_cmd = TRUE;      // По умолчанию выборка записей из DBF
    // BOOL is_delete_cmd = FALSE;     
    // BOOL is_fields_cmd = FALSE;     
    // BOOL is_length_cmd = FALSE;     
    // char *dbf_filename = NULL;
    // unsigned long start_rec = 0;
    // int limit = -1;
    
    // Используемые кодовые страницы
    // char *src_codepage = "CP866";
    // char *dst_codepage = "UTF-8";
    
    const struct option long_opts[] = {
              { "debug", no_argument, NULL, 'd' },
              { "log", no_argument, NULL, 'l' },
              { "version", no_argument, NULL, 'v' },
              { "help", no_argument, NULL, 'h' },
            //   { "dbf", required_argument, NULL, 'f' },
            //   { "cmd", required_argument, NULL, 'C' },
            //   { "where", required_argument, NULL, 'W' },
            //   { "start_rec", required_argument, NULL, 'B' },
            //   { "limit", required_argument, NULL, 'L' },
            //   { "fields", required_argument, NULL, 'F' },
            //   { "order_by", required_argument, NULL, 'O' },
            //   { "reverse", no_argument, NULL, 'R' },
            //   { "src_codepage", required_argument, NULL, 'S' },
            //   { "dst_codepage", required_argument, NULL, 'D' },
              { NULL, 0, NULL, 0 }
       };
  
    if (DebugMode) log_info("OPTIONS:");
    // while ((opt = getopt_long(argc, argv, "dlvhfCWLFORSD:", long_opts, NULL)) != -1)
    while ((opt = getopt_long(argc, argv, "dlvh:", long_opts, NULL)) != -1)
    {
        switch (opt)
            {
            case 'd':
                DebugMode = TRUE;
                if (DebugMode) log_info("\t--debug");
                break;

            case 'l':
                DebugMode = TRUE;
                if (DebugMode) log_info("\t--log");
                break;
                
            case 'h':
                print_help();
                if (DebugMode) log_info("\t--help");
                break;
                
            case 'v':
                print_version();
                if (DebugMode) log_info("\t--version");
                break;
                
            case '?':
                print_help();
                return TRUE;

            // case 'f':
            //     dbf_filename = optarg;
            //     if (DebugMode) log_info("\t--dbf = %s [%s]", dbf_filename, (exists_file(dbf_filename))?"+":"-");
            //     break;

            // case 'B':
            //     start_rec = atol(optarg);
            //     if (DebugMode) log_info("\t--start_rec = %s", optarg);
            //     break;
                                
            // case 'L':
            //     limit = atoi(optarg);
            //     if (DebugMode) log_info("\t--limit = %s", optarg);
            //     break;

            // case 'S':
            //     src_codepage = optarg;
            //     if (DebugMode) log_info("\t--src_codepage = %s", src_codepage);
            //     break;

            // case 'D':
            //     dst_codepage = optarg;
            //     if (DebugMode) log_info("\t--dst_codepage = %s", dst_codepage);
            //     break;
                
            // case 'C':
            //     if (strcmp(optarg, "SELECT") == 0)
            //     {
            //         is_select_cmd = TRUE;
            //         is_delete_cmd = FALSE;
            //         is_fields_cmd = FALSE;
            //         is_length_cmd = FALSE;
            //     }
            //     else if (strcmp(optarg, "DELETE") == 0)
            //     {
            //         is_select_cmd = FALSE;
            //         is_delete_cmd = TRUE;
            //         is_fields_cmd = FALSE;
            //         is_length_cmd = FALSE;
            //     }                
            //     else if (strcmp(optarg, "FIELDS") == 0)
            //     {
            //         is_select_cmd = FALSE;
            //         is_delete_cmd = FALSE;
            //         is_fields_cmd = TRUE;
            //         is_length_cmd = FALSE;
            //     }
            //     else if (strcmp(optarg, "LENGTH") == 0)
            //     {
            //         is_select_cmd = FALSE;
            //         is_delete_cmd = FALSE;
            //         is_fields_cmd = FALSE;
            //         is_length_cmd = TRUE;
            //     }
            //     if (DebugMode) log_info("\t--cmd = %s", optarg);
            //     break;
                
            default:
                fprintf(stderr, "Unknown parameter: \'%c\'", opt);
                return FALSE;
        }
    }

    // if (is_select_cmd)    
    //     print_select(dbf_filename, NULL, NULL, NULL, NULL, FALSE, start_rec, limit, 
    //                  src_codepage, dst_codepage);
    // else if (is_delete_cmd)    
    //     ;
    // else if (is_fields_cmd)
    //     print_fields(dbf_filename);
    // else if (is_length_cmd)
    //     print_record_count(dbf_filename);
                
    return 1;
}

