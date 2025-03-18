#include "Repo.h"
#include <vector>
#include <map>
#include <set>
#include <string>
#include "Command.h"
void Repo::execCode() {
    int Ak = 0;
    for (Command* cmd : commands) {
        std::vector <int> keys;
        for (auto curr : resultKeys) {
            keys.push_back(data[curr]);
            if (keys.size() == 3) {
                break;
           }
        }
        if (keys.size() == 2) {
            keys.push_back(Ak);
        }
        cmd->exec(keys[0], keys[1], keys[2]);
    }
}