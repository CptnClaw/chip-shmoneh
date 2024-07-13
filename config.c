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
	CONFIG.DEBUG = 0; 
	CONFIG.SHIFT_BEHAVIOR = 1;
	CONFIG.JUMP_OFFSET_BEHAVIOR = 0;
	CONFIG.ADD_INDEX_BEHAVIOR = 1;
	CONFIG.STORE_MEM_BEHAVIOR = 1;
	CONFIG.LOGIC_FLAG_BEHAVIOR = 1;

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
			else if (0 == strcmp(entry, "ADD_INDEX_BEHAVIOR"))
			{
				CONFIG.ADD_INDEX_BEHAVIOR = atoi(value);
			}
			else if (0 == strcmp(entry, "STORE_MEM_BEHAVIOR"))
			{
				CONFIG.STORE_MEM_BEHAVIOR = atoi(value);
			}
			else if (0 == strcmp(entry, "LOGIC_FLAG_BEHAVIOR"))
			{
				CONFIG.LOGIC_FLAG_BEHAVIOR = atoi(value);
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
	printf("ADD_INDEX_BEHAVIOR = %d\n", CONFIG.ADD_INDEX_BEHAVIOR);
	printf("STORE_MEM_BEHAVIOR = %d\n", CONFIG.STORE_MEM_BEHAVIOR);
	printf("LOGIC_FLAG_BEHAVIOR = %d\n", CONFIG.LOGIC_FLAG_BEHAVIOR);
}
