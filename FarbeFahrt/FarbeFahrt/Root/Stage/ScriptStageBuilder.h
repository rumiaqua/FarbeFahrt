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
				data.resourceList.insert(std::make_pair(s1, s2));
			}

			// �v���C���[���W
			if (split[0] == "p")
			{
				data.playerPosition = Vector3(
					String::ToValue<float>(split[1]),
					String::ToValue<float>(split[2]),
					String::ToValue<float>(split[3]));
			}

			// �t�B�[���h��
			if (split[0] == "f")
			{
				data.fieldName = split[1];
				data.fieldScale = String::ToValue<float>(split[2]);
			}

			// �X�J�C�h�[�����@���g�p
			if (split[0] == "s")
			{
				data.skyName = split[1];
			}

			// �I�u�W�F�N�g�z�u
			if (split[0] == "o")
			{
				// �p�����[�^���Ȃ���΋�̃p�����[�^���_�~�[�Ƃ��đ}������
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

	// �������䂦�g�p���Ȃ����ƁI
	void save(const String& filename, const StageData& data) const override
	{
		return;

		std::ofstream stream(filename.toNarrow());

		// ���\�[�X
		stream << "# Resources" << std::endl;
		for (auto&& resource : data.resourceList)
		{
			stream << 
				"r," <<
				resource.first << "," <<
				resource.second << std::endl;
		}

		// �v���C���[
		stream << "# Player" << std::endl;
		stream <<
			"p," <<
			data.playerPosition.x << "," <<
			data.playerPosition.y << "," <<
			data.playerPosition.z << std::endl;

		// �t�B�[���h
		stream << "# Field" << std::endl;
		stream << "f," << data.fieldName << std::endl;

		// �X�J�C�h�[��
		// stream << "# Skydome" << std::endl;
		// stream << "s," << data.skyName << std::endl;

		// �I�u�W�F�N�g
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
