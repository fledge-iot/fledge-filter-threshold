/*
 * Fledge "threshold" filter plugin.
 *
 * Copyright (c) 2019 Dianomic Systems
 *
 * Released under the Apache 2.0 Licence
 *
 * Author: Mark Riddoch
 */

#include <plugin_api.h>
#include <config_category.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string>
#include <iostream>
#include <filter_plugin.h>
#include <threshold.h>
#include <version.h>


#define FILTER_NAME "threshold"
static const char *def_cfg = QUOTE({
		"plugin" : { 
			"description" : "Variable readings collection threshold filter",
			"type" : "string", 
			"default" : FILTER_NAME,
			"readonly" : "true"
			},
		"enable": {
			"description": "A switch that can be used to enable or disable execution of the threshold filter.", 
			"type": "boolean",
			"displayName": "Enabled",
			"default": "false"
			},
		"expression": {
			"description": "The threshold expression to evaluate",
			"type": "string",
			"default": "",
			"order" : "1",
			"displayName" : "Expression"
			}
	});

using namespace std;

/**
 * The Filter plugin interface
 */
extern "C" {

/**
 * The plugin information structure
 */
static PLUGIN_INFORMATION info = {
        FILTER_NAME,              // Name
        VERSION,                  // Version
        0,                        // Flags
        PLUGIN_TYPE_FILTER,       // Type
        "1.0.0",                  // Interface version
	def_cfg	            	  // Default plugin configuration
};

/**
 * Return the information about this plugin
 */
PLUGIN_INFORMATION *plugin_info()
{
	return &info;
}

/**
 * Initialise the threshold plugin. This creates the underlying
 * object and prepares the filter for operation. This will be
 * called before any data is ingested
 *
 * @param config	The configuration category for the filter
 * @param outHandle	A handle that will be passed to the output stream
 * @param output	The output stream (function pointer) to which data is passed
 * @return		An opaque handle that is used in all subsequent calls to the plugin
 */
PLUGIN_HANDLE plugin_init(ConfigCategory *config,
			  OUTPUT_HANDLE *outHandle,
			  OUTPUT_STREAM output)
{
	ThresholdFilter *handle = new ThresholdFilter(FILTER_NAME,
						  *config,
						  outHandle,
						  output);
	
	return (PLUGIN_HANDLE)handle;
}

/**
 * Ingest a set of readings into the plugin for processing
 *
 * @param handle	The plugin handle returned from plugin_init
 * @param readingSet	The readings to process
 */
void plugin_ingest(PLUGIN_HANDLE *handle,
		   READINGSET *readingSet)
{
	ThresholdFilter *filter = (ThresholdFilter *)handle;
	if (!filter->isEnabled())
	{
		/*
		 * Current filter is not active: just pass the readings
		 * set along the filter chain
		 */
		filter->m_func(filter->m_data, readingSet);
		return;
	}

	/*
	 * Create a new vector for the output readings. This may contain
	 * a mixture of readings created by the plugin and readings from
	 * the reading set passed in. The filter class takes care of
	 * deleting any readings not passed up the chain.
	 *
	 * We create a new ReadingSet with the contains of the output
	 * vector, hence the readingSet passed in is deleted.
	 */
	vector<Reading *> out;
	filter->ingest(((ReadingSet *)readingSet)->getAllReadingsPtr(), out);
	delete (ReadingSet *)readingSet;

	/*
	 * Create a new reading set and pass it up the filter
	 * chain. Note this reading set may not contain any
	 * actual readings.
	 */
	ReadingSet *newReadingSet = new ReadingSet(&out);
	filter->m_func(filter->m_data, newReadingSet);
}

/**
 * Reconfigure the plugin
 *
 * @param handle	The plugin handle
 * @param newConfig	The updated configuration
 */
void plugin_reconfigure(PLUGIN_HANDLE *handle, const string& newConfig)
{
	ThresholdFilter *filter = (ThresholdFilter *)handle;
	filter->reconfigure(newConfig);
}

/**
 * Call the shutdown method in the plugin
 */
void plugin_shutdown(PLUGIN_HANDLE *handle)
{
	ThresholdFilter *filter = (ThresholdFilter *)handle;
	delete filter;
}

};
