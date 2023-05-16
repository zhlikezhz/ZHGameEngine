/**
 * @file GraphicConfig.hpp
 * @brief 
 * @author 邹浩 (zouhaodata@gmail.com)
 * @version 1.0.0
 * @date 2021-06-18
 * 
 * @copyright Copyright (c) 2021  UpPower Studio
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version   <th>Author   <th>Description
 * <tr><td>2021-06-18 <td>1.0.0     <td>邹浩     <td>内容
 * </table>
 */
#pragma once
#include <stdint.h>

namespace UpPower
{
	struct GraphicConfig 
	{
		/**
		 * @brief Construct a new Graphic Config object
		 * @param  width            屏幕宽
		 * @param  height           屏幕高
		 * @param  appName			app名字
		 */
		GraphicConfig(uint32_t width = 1920, uint32_t height = 1080, const char* appName="GraphicEngine") :
			m_iScreenWidth(width), m_iScreenHeight(height), m_pAppName(appName)
		{}

		uint32_t m_iScreenWidth;
		uint32_t m_iScreenHeight;
        const char* m_pAppName;
	};
}

