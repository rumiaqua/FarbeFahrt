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
			// コメント行
			if (buffer[0] == '#')
			{
				continue;
			}

			std::vector<String> split = String::Split(buffer, ',');

			if (split.empty())
			{
				continue;
			}

			// 使用リソース
			if (split[0] == "r")
			{
				String& s1 = split[1];
				String& s2 = split[2];
				data.resourceList.insert(std::make_pair(s1, s2));
			}

			// プレイヤー座標
			if (split[0] == "p")
			{
				data.playerPosition = Vector3(
					String::ToValue<float>(split[1]),
					String::ToValue<float>(split[2]),
					String::ToValue<float>(split[3]));
			}

			// フィールド名
			if (split[0] == "f")
			{
				data.fieldName = split[1];
				data.fieldScale = String::ToValue<float>(split[2]);
			}

			// スカイドーム名　未使用
			if (split[0] == "s")
			{
				data.skyName = split[1];
			}

			// オブジェクト配置
			if (split[0] == "o")
			{
				// パラメータがなければ空のパラメータをダミーとして挿入する
				if (split.size() < 8)
				{
					split.emplace_back("");
				}

				data.objectList.emplace_back(
					split[1],
					split[2],
					Vector3(
						String::ToValue<float>(split[3]),
						String::ToValue<float>(split[4]),
						String::ToValue<float>(split[5])),
					split[6],
					split[7]);
			}
		}
		return data;
	}

	// 未完成ゆえ使用しないこと！
	void save(const String& filename, const StageData& data) const override
	{
		return;

		std::ofstream stream(filename.toNarrow());

		// リソース
		stream << "# Resources" << std::endl;
		for (auto&& resource : data.resourceList)
		{
			stream << 
				"r," <<
				resource.first << "," <<
				resource.second << std::endl;
		}

		// プレイヤー
		stream << "# Player" << std::endl;
		stream <<
			"p," <<
			data.playerPosition.x << "," <<
			data.playerPosition.y << "," <<
			data.playerPosition.z << std::endl;

		// フィールド
		stream << "# Field" << std::endl;
		stream << "f," << data.fieldName << std::endl;

		// スカイドーム
		// stream << "# Skydome" << std::endl;
		// stream << "s," << data.skyName << std::endl;

		// オブジェクト
		stream << "# Objects" << std::endl;
		for (auto&& object : data.objectList)
		{
			stream <<
				"o," <<
				object.name << ","
				<< object.resource << "," <<
				object.position.x << "," <<
				object.position.y << "," <<
				object.position.z << std::endl;
			// stream << object.basicInfo();
			// stream << object.parameter() << std::endl;
		}
	}
};
