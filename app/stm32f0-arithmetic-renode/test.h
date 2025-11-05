#pragma once

class Test {
	public:
	virtual void setUp() = 0;
	virtual void run() = 0;
	virtual void tearDown() = 0;
	static bool suiteStarted;
	static bool suiteFinished;
	static unsigned startCount;
	static unsigned finishCount;
	static unsigned okCount;
	static unsigned failCount;

	template<typename T>
	void expectEq(T expected, T calculated) {
		if(expected == calculated) {
			okCount++;
		} else {
			failCount++;
		}
	}
};