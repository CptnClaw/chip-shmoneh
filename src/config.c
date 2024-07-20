#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

#define BUF_LEN 100
#define CONFIG_PATH "chip-shmoneh.conf"

/* This is the global configuration variable,
 * to be used elsewhere by including "config.h" (which has an extern statement)
 * and modified ONLY by the load_config function. */
struct Config CONFIG;

int load_config()
{
	/* Set default values */
	CONFIG.INSTRUCTIONS_PER_SECOND = 1000;
	CONFIG.DISPLAY_SCALE = 10;
	CONFIG.PIXEL_GRID_GAP = 0;
	CONFIG.DOUBLE_BUFFERING = 1;
	CONFIG.RENDER_UNCHANGED_FRAMES = 0;
	CONFIG.DEBUG = 0;
	CONFIG.SHIFT_BEHAVIOR = 1;
	CONFIG.JUMP_OFFSET_BEHAVIOR = 0;
	CONFIG.STORE_MEM_BEHAVIOR = 1;
	CONFIG.QUIRK_RESET_FLAG = 0;
	CONFIG.QUIRK_WAIT_VBLANK = 0;
	CONFIG.PIXEL_CLIP_BEHAVIOR = 1;
	CONFIG.CUSTOM_COLORS = 0;
	CONFIG.COLOR1 = 0xff00ff;
	CONFIG.COLOR2 = 0xff00ff;
	CONFIG.COLOR3 = 0xff00ff;
	CONFIG.COLOR4 = 0xff00ff;
	CONFIG.COLOR5 = 0xff00ff;
	CONFIG.COLOR6 = 0xff00ff;
	CONFIG.COLOR7 = 0xff00ff;
	CONFIG.COLOR8 = 0xff00ff;
	CONFIG.COLOR9 = 0xff00ff;
	CONFIG.COLOR10 = 0xff00ff;
	CONFIG.COLOR11 = 0xff00ff;
	CONFIG.COLOR12 = 0xff00ff;
	CONFIG.COLOR13 = 0xff00ff;
	CONFIG.COLOR14 = 0xff00ff;
	CONFIG.COLOR15 = 0xff00ff;
	CONFIG.COLOR16 = 0xff00ff;
	CONFIG.COLOR17 = 0xff00ff;
	CONFIG.COLOR18 = 0xff00ff;
	CONFIG.COLOR19 = 0xff00ff;
	CONFIG.COLOR20 = 0xff00ff;
	CONFIG.COLOR21 = 0xff00ff;
	CONFIG.COLOR22 = 0xff00ff;
	CONFIG.COLOR23 = 0xff00ff;
	CONFIG.COLOR24 = 0xff00ff;
	CONFIG.COLOR25 = 0xff00ff;
	CONFIG.COLOR26 = 0xff00ff;
	CONFIG.COLOR27 = 0xff00ff;
	CONFIG.COLOR28 = 0xff00ff;
	CONFIG.COLOR29 = 0xff00ff;
	CONFIG.COLOR30 = 0xff00ff;
	CONFIG.COLOR31 = 0xff00ff;
	CONFIG.COLOR32 = 0xff00ff;

	/* Set values from configuration file */
	FILE *file;
	char line[BUF_LEN];
	char *comment;
	char *entry;
	char *value;
	file = fopen(CONFIG_PATH , "r");
	if (file == NULL)
	{
		printf("Error opening configuration file.\n");
		return 0;
	}
	while (fgets(line, BUF_LEN, file) != NULL)
	{
		/* Remove comment */
		comment = strchr(line, '#');
		if (comment != NULL)
		{
			*comment = '\n';
			*(comment+1) = '\0';
		}

		if (line[0] != '\n')
		{
			entry = strtok(line, " \t");
			value = strtok(NULL, " \t");
			if (entry == NULL || value == NULL)
			{
				printf("Configuration parsing error");
				return 0;
			}
			if (0 == strcmp(entry, "INSTRUCTIONS_PER_SECOND"))
			{
				CONFIG.INSTRUCTIONS_PER_SECOND = atoi(value);
			}
			else if (0 == strcmp(entry, "DISPLAY_SCALE"))
			{
				CONFIG.DISPLAY_SCALE = atoi(value);
			}
			else if (0 == strcmp(entry, "PIXEL_GRID_GAP"))
			{
				CONFIG.PIXEL_GRID_GAP = atoi(value);
			}
			else if (0 == strcmp(entry, "DOUBLE_BUFFERING"))
			{
				CONFIG.DOUBLE_BUFFERING = atoi(value);
			}
			else if (0 == strcmp(entry, "RENDER_UNCHANGED_FRAMES"))
			{
				CONFIG.RENDER_UNCHANGED_FRAMES = atoi(value);
			}
			else if (0 == strcmp(entry, "DEBUG"))
			{
				CONFIG.DEBUG = atoi(value);
			}
			else if (0 == strcmp(entry, "SHIFT_BEHAVIOR"))
			{
				CONFIG.SHIFT_BEHAVIOR = atoi(value);
			}
			else if (0 == strcmp(entry, "JUMP_OFFSET_BEHAVIOR"))
			{
				CONFIG.JUMP_OFFSET_BEHAVIOR = atoi(value);
			}
			else if (0 == strcmp(entry, "STORE_MEM_BEHAVIOR"))
			{
				CONFIG.STORE_MEM_BEHAVIOR = atoi(value);
			}
			else if (0 == strcmp(entry, "QUIRK_RESET_FLAG"))
			{
				CONFIG.QUIRK_RESET_FLAG = atoi(value);
			}
			else if (0 == strcmp(entry, "QUIRK_WAIT_VBLANK"))
			{
				CONFIG.QUIRK_WAIT_VBLANK = atoi(value);
			}
			else if (0 == strcmp(entry, "PIXEL_CLIP_BEHAVIOR"))
			{
				CONFIG.PIXEL_CLIP_BEHAVIOR = atoi(value);
			}
			else if (0 == strcmp(entry, "CUSTOM_COLORS"))
			{
				CONFIG.CUSTOM_COLORS = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR1"))
			{
				CONFIG.COLOR1 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR2"))
			{
				CONFIG.COLOR2 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR2"))
			{
				CONFIG.COLOR2 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR3"))
			{
				CONFIG.COLOR3 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR3"))
			{
				CONFIG.COLOR3 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR4"))
			{
				CONFIG.COLOR4 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR5"))
			{
				CONFIG.COLOR5 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR6"))
			{
				CONFIG.COLOR6 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR7"))
			{
				CONFIG.COLOR7 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR8"))
			{
				CONFIG.COLOR8 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR9"))
			{
				CONFIG.COLOR9 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR10"))
			{
				CONFIG.COLOR10 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR11"))
			{
				CONFIG.COLOR11 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR12"))
			{
				CONFIG.COLOR12 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR13"))
			{
				CONFIG.COLOR13 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR14"))
			{
				CONFIG.COLOR14 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR15"))
			{
				CONFIG.COLOR15 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR16"))
			{
				CONFIG.COLOR16 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR17"))
			{
				CONFIG.COLOR17 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR18"))
			{
				CONFIG.COLOR18 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR19"))
			{
				CONFIG.COLOR19 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR20"))
			{
				CONFIG.COLOR20 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR21"))
			{
				CONFIG.COLOR21 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR22"))
			{
				CONFIG.COLOR22 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR23"))
			{
				CONFIG.COLOR23 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR24"))
			{
				CONFIG.COLOR24 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR25"))
			{
				CONFIG.COLOR25 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR26"))
			{
				CONFIG.COLOR26 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR27"))
			{
				CONFIG.COLOR27 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR28"))
			{
				CONFIG.COLOR28 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR29"))
			{
				CONFIG.COLOR29 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR30"))
			{
				CONFIG.COLOR30 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR31"))
			{
				CONFIG.COLOR31 = atoi(value);
			}
			else if (0 == strcmp(entry, "COLOR32"))
			{
				CONFIG.COLOR32 = atoi(value);
			}
			else
			{
				printf("Invalid configuration entry: %s\n", entry);
				return 0;
			}
		}
	}
	fclose(file);

	if (CONFIG.PIXEL_GRID_GAP < 0 ||
		CONFIG.PIXEL_GRID_GAP > CONFIG.DISPLAY_SCALE / 2)
	{
		printf("Invalid configuration value PIXEL_GRID_GAP=%d", CONFIG.PIXEL_GRID_GAP);
		return 0;
	}

	return 1;
}


void print_config()
{
	printf("INSTRUCTIONS_PER_SECOND = %d\n", CONFIG.INSTRUCTIONS_PER_SECOND);
	printf("DISPLAY_SCALE = %d\n", CONFIG.DISPLAY_SCALE);
	printf("PIXEL_GRID_GAP = %d\n", CONFIG.PIXEL_GRID_GAP);
	printf("DEBUG = %d\n", CONFIG.DEBUG );
	printf("SHIFT_BEHAVIOR = %d\n", CONFIG.SHIFT_BEHAVIOR);
	printf("JUMP_OFFSET_BEHAVIOR = %d\n", CONFIG.JUMP_OFFSET_BEHAVIOR);
	printf("STORE_MEM_BEHAVIOR = %d\n", CONFIG.STORE_MEM_BEHAVIOR);
	printf("QUIRK_RESET_FLAG = %d\n", CONFIG.QUIRK_RESET_FLAG);
	printf("CUSTOM_COLORS = %d\n", CONFIG.CUSTOM_COLORS);
	printf("COLOR1 = %d\n", CONFIG.COLOR1);
	printf("COLOR2 = %d\n", CONFIG.COLOR2);
	printf("COLOR3 = %d\n", CONFIG.COLOR3);
	printf("COLOR4 = %d\n", CONFIG.COLOR4);
	printf("COLOR5 = %d\n", CONFIG.COLOR5);
	printf("COLOR6 = %d\n", CONFIG.COLOR6);
	printf("COLOR7 = %d\n", CONFIG.COLOR7);
	printf("COLOR8 = %d\n", CONFIG.COLOR8);
	printf("COLOR9 = %d\n", CONFIG.COLOR9);
	printf("COLOR10 = %d\n", CONFIG.COLOR10);
	printf("COLOR11 = %d\n", CONFIG.COLOR11);
	printf("COLOR12 = %d\n", CONFIG.COLOR12);
	printf("COLOR13 = %d\n", CONFIG.COLOR13);
	printf("COLOR14 = %d\n", CONFIG.COLOR14);
	printf("COLOR15 = %d\n", CONFIG.COLOR15);
	printf("COLOR16 = %d\n", CONFIG.COLOR16);
	printf("COLOR17 = %d\n", CONFIG.COLOR17);
	printf("COLOR18 = %d\n", CONFIG.COLOR18);
	printf("COLOR19 = %d\n", CONFIG.COLOR19);
	printf("COLOR20 = %d\n", CONFIG.COLOR20);
	printf("COLOR21 = %d\n", CONFIG.COLOR21);
	printf("COLOR22 = %d\n", CONFIG.COLOR22);
	printf("COLOR23 = %d\n", CONFIG.COLOR23);
	printf("COLOR24 = %d\n", CONFIG.COLOR24);
	printf("COLOR25 = %d\n", CONFIG.COLOR25);
	printf("COLOR26 = %d\n", CONFIG.COLOR26);
	printf("COLOR27 = %d\n", CONFIG.COLOR27);
	printf("COLOR28 = %d\n", CONFIG.COLOR28);
	printf("COLOR29 = %d\n", CONFIG.COLOR29);
	printf("COLOR30 = %d\n", CONFIG.COLOR30);
	printf("COLOR31 = %d\n", CONFIG.COLOR31);
	printf("COLOR32 = %d\n", CONFIG.COLOR32);
}
