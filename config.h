#ifndef CONFIG_H
#define CONFIG_H

#define sz(x) ((int) (x).size())
#define foreach(x, y) \
	for(__typeof((y).begin()) x = (y).begin(); x != (y).end(); ++x)

#endif

