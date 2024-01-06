#include "Trie.h"
#include <Windows.h>
#include <conio.h>
void main()
{
	char buf[1000];
	string res;
	TrieNode* root = getNewNode();
	insert(root, "a");
	insert(root, "hero");
	insert(root, "the");
	cout << "\nEnter:insert new word ,Tab to find prefixes in trie ,Del to remove word, Esc to exit\n";
	
    while (true)
    {
        if (_kbhit()) // слушатель нажатия на клаву
        {
            switch (_getch()) // ждёт нажатия на клаву без Enter после этого
            {
            case 9: //tab
			{
				cout << "input word:";
				string tmp;
				cin >> tmp;
				if (search(root, tmp)) { cout << tmp << " is a word in the trie\n"; }
				findWords(wordjump(root, tmp), buf, 0, res);
				if (res[0] == ' ') { res.clear(); break; }
				cout << tmp << "+" << res << endl;
				res.clear();
				cout << "\nEnter:insert new word ,Tab to find prefixes in trie ,Del to remove word, Esc to exit\n";
				break;
			}
			case 13:  //enter
				cout << "input word:";
				cin >> buf;
				if (search(root, string(buf))) { cout << "word is already in trie\n"; break; };
				insert(root, string(buf));
				cout << "\nEnter:insert new word ,Tab to find prefixes in trie ,Del to remove word, Esc to exit\n";
				break;
			case 224: //del
			{
				cout << "input word:";
				string tmp;
				cin >> tmp;
				remove(root, tmp, 0 );
				cout << "\nEnter:insert new word ,Tab to find prefixes in trie ,Del to remove word, Esc to exit\n";
				break;
			}
            case 27: //esc
				return;
            }
        }
    }
	return;
}