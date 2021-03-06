# pragma once

# include "Utility/String.h"

# include <fstream>

# include "MessageData.h"

class MessageScriptLoader
{
public:

	void load(const std::string& filename, MessageData& output)
	{
		while (!output.operationQueue.empty())
		{
			output.operationQueue.pop();
		}

		std::fstream stream { filename };
		std::string buffer;

		while (std::getline(stream, buffer))
		{
			auto split = String::Split(buffer, ',');
			if (split.size() < 2)
			{
				split.emplace_back("");
			}

			output.add(split[0], split[1]);
		}
	}
};
