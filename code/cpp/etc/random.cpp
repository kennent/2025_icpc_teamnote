// init
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dis(0, n);
// use
int x = dis(gen);