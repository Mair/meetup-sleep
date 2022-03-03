idf_component_register(SRCS 

                        "main.c"
                        "concepts/__benchmark_online.c"                  
                        "concepts/_1_light_sleep_timer.c"
                        "concepts/_2_light_GPIO.c"
                        "concepts/_3_deep_sleep_timer.c"
                        "concepts/_4_deep_sleep_EXT_0.c"
                        "concepts/_5_deep_sleep_EXT_1.c"
                        "concepts/_6_hibernation.c"
                        "concepts/_7_keepTime.c"
                    INCLUDE_DIRS 
                        "concepts"
                        "."
                    EMBED_TXTFILES
                    "../cert/cert.cer")
