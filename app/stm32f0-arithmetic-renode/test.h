#pragma once

class Test {
	public:
	virtual void setUp() {};
	virtual void run() = 0;
	virtual void tearDown() {};
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

class TestIMult : public Test {
	public:
	void run() override;
};

class TestIBasic : public Test {
	public:
	void run() override;
};
