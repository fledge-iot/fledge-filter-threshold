#ifndef _THRESHOLD_FILTER_H
#define _THRESHOLD_FILTER_H

/*
 * Fledge "threshold" filter plugin.
 *
 * Copyright (c) 2019 Dianomic Systems
 *
 * Released under the Apache 2.0 Licence
 *
 * Author: Mark Riddoch           
 */     
#include <filter.h>               
#include <reading_set.h>
#include <config_category.h>
#include <string>                 
#include <logger.h>
#include <list>
#include <vector>
#include <map>
#include <mutex>


/**
 * A threshold filter class.
 *
 * Only send data on when a threshold expression evaluates to true
 */
class ThresholdFilter : public FledgeFilter {
	public:
		ThresholdFilter(const std::string& filterName,
                        ConfigCategory& filterConfig,
                        OUTPUT_HANDLE *outHandle,
                        OUTPUT_STREAM out);
		~ThresholdFilter();
		void	ingest(std::vector<Reading *> *readings, std::vector<Reading *>& out);
		void	reconfigure(const std::string& newConfig);
		void	setExpression(const std::string& expression)
			{
				m_expression = expression;
			};
	private:
		void 			handleConfig(const ConfigCategory& conf);
		bool			m_triggered;
		std::string		m_expression;
		std::mutex		m_configMutex;
};



#endif
