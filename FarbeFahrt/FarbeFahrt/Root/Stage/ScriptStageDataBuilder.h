# pragma once

# include "IStageDataBuilder.h"

# include <fstream>

class ScriptStageDataBuilder final : public IStageDataBuilder
{
public:

	StageData open(const std::string& filename) const override
	{
		StageData data;

		return open(filename, data);
	}

	StageData& open(const std::string& filename, StageData& output) const override
	{
		// 初期化
		output.resourceList.clear();
		output.fieldList.clear();
		output.objectList.clear();
		output.message.clear();

		// 初期値を代入
		output.filename = filename;
		output.endName.clear();
		output.bgmName = "";

		// テキストのロードを開始
		std::ifstream stream(filename);

		std::string buffer;
		while (std::getline(stream, buffer))
		{
			// コメント行
			if (buffer[0] == '#')
			{
				continue;
			}

			// 文字列をカンマ区切りで解析
			std::vector<std::string> split = String::Split(buffer, ',');

			// 区切った結果空であれば不正なので読み飛ばし
			// 空であることってあるのか？
			if (split.empty())
			{
				continue;
			}

			// 使用リソース
			if (split[0] == "r")
			{
				std::string& s1 = split[1];
				std::string& s2 = split[2];
				output.resourceList.insert(std::make_pair(s1, s2));
			}

			// プレイヤー座標
			if (split[0] == "p")
			{
				output.playerPosition = Vector3(
					String::ToValue<float>(split[1]),
					String::ToValue<float>(split[2]),
					String::ToValue<float>(split[3]));
			}

			// フィールド名
			if (split[0] == "f")
			{
				std::string name = split[1];
				Vector3 position = Vector3(
					String::ToValue<float>(split[2]),
					String::ToValue<float>(split[3]),
					String::ToValue<float>(split[4]));
				float scale = String::ToValue<float>(split[5]);
				std::string transition = "Resources/Script/Animation/Default.txt";
				if (split.size() > 6)
				{
					transition = split[6];
				}
				output.fieldList.emplace_back(name, position, scale, transition);
			}

			// オブジェクト配置
			if (split[0] == "o")
			{
				// パラメータがなければ空のパラメータをダミーとして挿入する
				if (split.size() < 8)
				{
					split.emplace_back("");
				}

				// オブジェクトリストに
				// クラス名
				// リソース名
				// x座標
				// y座標
				// z座標
				// 衝突図形
				// パラメータ
				// で追加する
				output.objectList.emplace_back(
					split[1],
					split[2],
					Vector3(
						String::ToValue<float>(split[3]),
						String::ToValue<float>(split[4]),
						String::ToValue<float>(split[5])),
					split[6],
					split[7]);
			}

			// 次のステージ
			if (split[0] == "n")
			{
				output.nextStage.first = split[1];
				output.nextStage.second = split[2];
				int threshold = 1;
				if (split.size() > 3)
				{
					threshold = String::ToValue<int>(split[3]);
				}
				output.threshold = threshold;
			}

			// エンド
			if (split[0] == "e")
			{
				std::string endName = split[1];
				std::string showStaffRoll = split[2];
				output.endName = endName;
				output.showStaffRoll = showStaffRoll == "show" ? true : false;
			}

			// メッセージ
			if (split[0] == "t")
			{
				output.message = split[1];
			}

			// 次のステージへのスイッチの起動変数
			if (split[0] == "g")
			{
				int gimmickPoint = String::ToValue<int>(split[1]);
				output.gimmickPoint = gimmickPoint;
			}

			// BGM
			if (split[0] == "bgm")
			{
				output.bgmName = split[1];
			}
		}

		return output;
	}

	// 未完成ゆえ使用しないこと！
	void save(const std::string& filename, const StageData& data) const override
	{
		return;
	}
};
