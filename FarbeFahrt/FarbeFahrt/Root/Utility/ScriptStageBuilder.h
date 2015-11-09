# pragma once

# include "IStageBuilder.h"

# include <fstream>

class ScriptStageBuilder final : public IStageBuilder
{
public:

	StageData open(const String& filename) const override
	{
		StageData data;

		std::ifstream stream(filename.toNarrow());

		std::string buffer;
		while (std::getline(stream, buffer))
		{
			if (buffer[0] == '#')
			{
				continue;
			}

			std::vector<String> split = String::Split(buffer, ',');

			if (split.empty())
			{
				continue;
			}

			if (split[0] == "r")
			{
				data.resourceList.insert(std::make_pair(split[1], split[2]));
			}

			if (split[0] == "p")
			{
				data.playerPosition = Vector3(
					String::ToValue<float>(split[1]),
					String::ToValue<float>(split[2]),
					String::ToValue<float>(split[3]));
			}

			if (split[0] == "f")
			{
				data.fieldName = split[1];
				data.fieldScale = String::ToValue<float>(split[2]);
			}

			if (split[0] == "s")
			{
				data.skyName = split[1];
			}

			if (split[0] == "o")
			{
				data.objectList.emplace_back(split[1], split[2], Vector3(
						String::ToValue<float>(split[3]),
						String::ToValue<float>(split[4]),
						String::ToValue<float>(split[5])), nullptr);
			}
		}
		return data;
	}

	void save(const String& filename, const StageData& data) const override
	{
		std::ofstream stream(filename.toNarrow());

		stream << "# Resources" << std::endl;

		// リソース
		for (auto&& resource : data.resourceList)
		{
			stream << 
				"r," <<
				resource.first << "," <<
				resource.second << std::endl;
		}

		stream << "# Player" << std::endl;

		// プレイヤー
		stream <<
			"p," <<
			data.playerPosition.x << "," <<
			data.playerPosition.y << "," <<
			data.playerPosition.z << std::endl;

		stream << "f," << data.fieldName << std::endl;

		stream << "s," << data.skyName << std::endl;

		stream << "# Objects" << std::endl;

		// オブジェクト
		for (auto&& object : data.objectList)
		{
			stream <<
				"o," <<
				object.name << ","
				<< object.resource << "," <<
				object.position.x << "," <<
				object.position.y << "," <<
				object.position.z << std::endl;
		}
	}
};
