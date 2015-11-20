# pragma once

# include "IStageDataBuilder.h"

# include <fstream>

class ScriptStageDataBuilder final : public IStageDataBuilder
{
public:

	StageData open(const String& filename) const override
	{
		StageData data;

		return open(filename, data);
	}

	StageData& open(const String& filename, StageData& output) const override
	{
		output.resourceList.clear();
		output.fieldList.clear();
		output.objectList.clear();

		std::ifstream stream(filename.toNarrow());

		std::string buffer;
		while (std::getline(stream, buffer))
		{
			// �R�����g�s
			if (buffer[0] == '#')
			{
				continue;
			}

			std::vector<String> split = String::Split(buffer, ',');

			if (split.empty())
			{
				continue;
			}

			// �g�p���\�[�X
			if (split[0] == "r")
			{
				String& s1 = split[1];
				String& s2 = split[2];
				output.resourceList.insert(std::make_pair(s1, s2));
			}

			// �v���C���[���W
			if (split[0] == "p")
			{
				output.playerPosition = Vector3(
					String::ToValue<float>(split[1]),
					String::ToValue<float>(split[2]),
					String::ToValue<float>(split[3]));
			}

			// �t�B�[���h��
			if (split[0] == "f")
			{
				String name = split[1];
				Vector3 position = Vector3(
					String::ToValue<float>(split[2]),
					String::ToValue<float>(split[3]),
					String::ToValue<float>(split[4]));
				float scale = String::ToValue<float>(split[5]);
				output.fieldList.emplace_back(name, position, scale);
			}

			// �X�J�C�h�[�����@���g�p
			if (split[0] == "s")
			{
				// data.skyName = split[1];
			}

			// �I�u�W�F�N�g�z�u
			if (split[0] == "o")
			{
				// �p�����[�^���Ȃ���΋�̃p�����[�^���_�~�[�Ƃ��đ}������
				if (split.size() < 8)
				{
					split.emplace_back("");
				}

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

			// ���̃X�e�[�W
			if (split[0] == "n")
			{
				output.nextStage.first = split[1];
				output.nextStage.second = split[2];
			}
		}

		return output;
	}

	// �������䂦�g�p���Ȃ����ƁI
	void save(const String& filename, const StageData& data) const override
	{
		return;
	}
};
