CC=gcc
CXX=g++
CCFLAGS= -g

all: HashTableTemplateTest HashTableVoidTest ListTemplateTest wcTemplate wcVoid

HashTableTemplateTest: HashTableTemplate.h HashTableTemplateTest.cc
	$(CXX) -o HashTableTemplateTest HashTableTemplateTest.cc

HashTableVoidTest: HashTableVoid.h HashTableVoidTest.cc
	$(CXX) -o HashTableVoidTest HashTableVoid.cc HashTableVoidTest.cc

ListTemplateTest: ListTemplate.h ListTemplateTest.cc
	$(CXX) -o ListTemplateTest ListTemplateTest.cc

wcVoid: wcVoid.cc HashTableVoid.h HashTableVoid.cc
	$(CXX) -o wcVoid wcVoid.cc HashTableVoid.cc

wcTemplate: wcTemplate.cc
	$(CXX) -o wcTemplate wcTemplate.cc

test:
	rm -f test_results
	ListTemplateTest && \
		(echo "ListTemplateTest OK" >> test_results) || \
		(echo "ListTemplateTest Failed" >> test_results) && \
	HashTableTemplateTest test1 && \
		(echo "HashTableTemplateTest test1  OK" >> test_results) || \
		(echo "HashTableTemplateTest test1  Failed" >> test_results) && \
	HashTableTemplateTest test2 && \
		(echo "HashTableTemplateTest test2  OK" >> test_results) || \
		(echo "HashTableTemplateTest test2  Failed" >> test_results) && \
	HashTableTemplateTest test3 && \
		(echo "HashTableTemplateTest test3  OK" >> test_results) || \
		(echo "HashTableTemplateTest test3  Failed" >> test_results) && \
	HashTableTemplateTest test4 && \
		(echo "HashTableTemplateTest test4  OK" >> test_results) || \
		(echo "HashTableTemplateTest test4  Failed" >> test_results) && \
	HashTableTemplateTest test5 && \
		(echo "HashTableTemplateTest test5  OK" >> test_results) || \
		(echo "HashTableTemplateTest test5  Failed" >> test_results) && \
	HashTableTemplateTest test6 && \
		(echo "HashTableTemplateTest test6  OK" >> test_results) || \
		(echo "HashTableTemplateTest test6  Failed" >> test_results) && \
	HashTableVoidTest test1 && \
		(echo "HashTableVoidTest test1  OK" >> test_results) || \
		(echo "HashTableVoidTest test1  Failed" >> test_results) && \
	HashTableVoidTest test2 && \
		(echo "HashTableVoidTest test2  OK" >> test_results) || \
		(echo "HashTableVoidTest test2  Failed" >> test_results) && \
	HashTableVoidTest test3 && \
		(echo "HashTableVoidTest test3  OK" >> test_results) || \
		(echo "HashTableVoidTest test3  Failed" >> test_results) && \
	HashTableVoidTest test4 && \
		(echo "HashTableVoidTest test4  OK" >> test_results) || \
		(echo "HashTableVoidTest test4  Failed" >> test_results) && \
	HashTableVoidTest test5 && \
		(echo "HashTableVoidTest test5  OK" >> test_results) || \
		(echo "HashTableVoidTest test5  Failed" >> test_results) && \
	HashTableVoidTest test6 && \
		(echo "HashTableVoidTest test6  OK" >> test_results) || \
		(echo "HashTableVoidTest test6  Failed" >> test_results) && \
	(wcVoid greetings.txt | sort > out1) && (wcVoidExample greetings.txt | sort > out2) && \
		diff out1 out2 && \
		(echo "wcVoid greetings.txt OK" >> test_results) || \
		(echo "wcVoid greetings.txt Failed" >> test_results) && \
	(wcTemplate greetings.txt | sort > out1) && (wcVoidExample greetings.txt | sort > out2) && \
		diff out1 out2 && \
		(echo "wcTemplate greetings.txt OK" >> test_results) || \
		(echo "wcTemplate greetings.txt Failed" >> test_results) && \
	echo && \
	echo ------ Test Results ----- && \
	cat test_results 

clean:
	rm -f core *.o HashTableTemplateTest HashTableVoidTest ListTemplateTest \
		wcVoid wcTemplate out1 out2 test_results

