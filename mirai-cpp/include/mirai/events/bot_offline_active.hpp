#pragma once
#ifndef mirai_cpp_events_bot_offline_active_hpp_H_
#define mirai_cpp_events_bot_offline_active_hpp_H_

#include "mirai/third-party/nlohmann/json.hpp"
#include "mirai/defs/qq_types.hpp"
#include "event_interface.hpp"

namespace Cyan
{
	/**
	 * \brief bot 主动离线事件
	 */
	class BotOfflineEventActive : public EventBase
	{
	public:
		QQ_t QQ;

		static MiraiEvent GetMiraiEvent()
		{
			return MiraiEvent::BotOfflineEventActive;
		}

		virtual bool Set(const json& j) override
		{
			this->QQ = (QQ_t)(j["qq"].get<int64_t>());
			return true;
		}
		virtual json ToJson() const override
		{
			json j = json::object();
			j["type"] = "BotOfflineEventActive";
			j["qq"] = (int64_t)this->QQ;
			return j;
		}
	};

}

#endif // !mirai_cpp_events_bot_offline_active_hpp_H_