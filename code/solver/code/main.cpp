#include "TemUnt/Code.hpp"
#include "TemUnt/Encoding.hpp"
#include "TemUnt/Situation.hpp"

#include <queue>
#include <unordered_map>


class Proto
{
public:
	TemUnt::Code getInitialSituation()
	{
		return 0b1000'0000'0000'0000'0000'0000'0000'0000;
	}
};


int main()
{
	Proto proto;
	std::queue<TemUnt::Code> codesToProcess;
	codesToProcess.push(proto.getInitialSituation());
	std::unordered_map<TemUnt::Code, TemUnt::Code> predecessors;
	predecessors.emplace(codesToProcess.front(), TemUnt::Encoding::StartState());
	//std::size_t currentDistance = 0, currentDistanceCount = 1;
	while (!codesToProcess.empty()) {
		auto current = TemUnt::Situation::fromCode(codesToProcess.front());
		for (auto next : current.iterateNeighbours()) {
			if (next == TemUnt::Encoding::Victory()) {
				// Goal found
				break; // #ToDo
			}
			auto& predecessor = predecessors[next];
			if (predecessor == TemUnt::Code{}) {
				predecessor = current.getCode();
				codesToProcess.push(next);
			}
		}
		codesToProcess.pop();
		//currentDistanceCount -= 1;
	}
}
