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
		// ������
		output.resourceList.clear();
		output.fieldList.clear();
		output.objectList.clear();
		output.message.clear();

		// �����l����
		output.filename = filename;
		output.endName.clear();
		output.bgmName = "";

		// �e�L�X�g�̃��[�h���J�n
		std::ifstream stream(filename);

		std::string buffer;
		while (std::getline(stream, buffer))
		{
			// �R�����g�s
			if (buffer[0] == '#')
			{
				continue;
			}

			// ��������J���}��؂�ŉ��
			std::vector<std::string> split = String::Split(buffer, ',');

			// ��؂������ʋ�ł���Εs���Ȃ̂œǂݔ�΂�
			// ��ł��邱�Ƃ��Ă���̂��H
			if (split.empty())
			{
				continue;
			}

			// �g�p���\�[�X
			if (split[0] == "r")
			{
				std::string& s1 = split[1];
				std::string& s2 = split[2];
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

			// �I�u�W�F�N�g�z�u
			if (split[0] == "o")
			{
				// �p�����[�^���Ȃ���΋�̃p�����[�^���_�~�[�Ƃ��đ}������
				if (split.size() < 8)
				{
					split.emplace_back("");
				}

				// �I�u�W�F�N�g���X�g��
				// �N���X��
				// ���\�[�X��
				// x���W
				// y���W
				// z���W
				// �Փː}�`
				// �p�����[�^
				// �Œǉ�����
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
				int threshold = 1;
				if (split.size() > 3)
				{
					threshold = String::ToValue<int>(split[3]);
				}
				output.threshold = threshold;
			}

			// �G���h
			if (split[0] == "e")
			{
				std::string endName = split[1];
				std::string showStaffRoll = split[2];
				output.endName = endName;
				output.showStaffRoll = showStaffRoll == "show" ? true : false;
			}

			// ���b�Z�[�W
			if (split[0] == "t")
			{
				output.message = split[1];
			}

			// ���̃X�e�[�W�ւ̃X�C�b�`�̋N���ϐ�
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

	// �������䂦�g�p���Ȃ����ƁI
	void save(const std::string& filename, const StageData& data) const override
	{
		return;
	}
};
