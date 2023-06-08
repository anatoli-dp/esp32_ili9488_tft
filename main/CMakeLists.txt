idf_component_register(
        SRCS
            "main.c"

            "display/spidriver/spi_master_lobo.c"

            "display/tft/tftspi.c"
            "display/tft/tft.c"

            "display/tft/minya24.c"

            "display/tft/comic24.c"
            "display/tft/def_small.c"
            "display/tft/DefaultFont.c"
            "display/tft/DejaVuSans18.c"
            "display/tft/DejaVuSans24.c"
            "display/tft/SmallFont.c"
            "display/tft/tooney32.c"
            "display/tft/Ubuntu16.c"
        INCLUDE_DIRS
        "."
        "./display"
        "./display/spidriver"
        "./display/tft"
)
