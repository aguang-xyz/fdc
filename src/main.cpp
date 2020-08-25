#include <fstream>

#include "fdc/fdc.h"

using namespace std;
using namespace fdc;

int main(int argc, char **argv) {

  if (argc != 2) {
    cout << "Usage: " << argv[0] << " [path]" << endl;
    return 0;
  }

  int N;

  fds F = fds();

  ifstream json = ifstream(argv[1]);

  from_json(json, N, F);

  fds G = mini(N, F);

  return 0;
}
