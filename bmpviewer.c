#include <stdio.h>
#include <stdlib.h>     // for exit


#include "bmpviewer.h"
#include "libfbdev.h"
#include "bitmapFileHeader.h"

void usage(void)
{
    printf("====================================================\n");
    printf("\nUsage: ./bitmap [FILE.bmp]\n");
    printf("====================================================\n");
}
void FrameBuffer_init(void)
{
    int screen_width;
    int screen_height;
    int bits_per_pixel;
    int line_length;
    //FrameBuffer init
    if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 )
	{
		printf ("FrameBuffer Init Failed\r\n");
		return 0;
	}
}

void Clear_FB(void)
{
	//Clear FB.
	fb_clear();
}

int bmp_open(char *name)
{
    int cols = 0, rows = 0;
	char *data;

    if (read_bmp(name, &data, &cols, &rows) < 0)
	{
		printf ("File open failed\r\n");
		return 0;
	}

	//FileWrite
	fb_write(data, cols,rows);
    
	close_bmp();
	fb_close();    
    return 0;
}
