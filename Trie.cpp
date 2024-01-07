
#include "Trie.h"

using namespace std;
// Âîçâðàùåò íîâûé óçåë ñ ïóñòûìè äåòüìè
TrieNode* getNewNode(void)
{
    // Âûäåëÿåì ïàìÿòü ïî íîâûé óçåë
    struct TrieNode* pNode = new TrieNode;

    // óñòàíàâëèâàåì ôëàã êîíöà ñëîâà â false
    pNode->isEndOfWord = false;

    // èíèöèàëèçèðóåì äåòåé íóëåâûì óàçàòåëåì
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}


// Âñòàâëÿåò êëþ÷ â äåðåâî, åñëè åãî íåò, 
// èíà÷å åñëè êëþ÷ ÿâëåòñÿ ïðåôêñîì óçëà äåðåâà 
// ïîìå÷àåò âêà÷åñòâå ëèòîâîãî ò.å. êîíåö ñëîâà
void insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // âû÷èñëÿåì èíäåêñ â àëôèòå ÷åðåç ñìåùåíèå îòíñèòüåëüíî ïåðâîé áóêâû
        int index = key[i] - 'a';

        // åñëè óêàçàòåëü ïóñòðîé, ò.å. äåòåé ñ òàêèì ïðåôèêñîì íåò
        // ñîçäàåì íîâûé óçåë
        if (!node->children[index]) {
            node->children[index] = getNewNode();
        }
        node->freq++;
        node = node->children[index];
    }
    node->freq++;
    // ïîìå÷àåì ïîñëåäíèé óçëåë êàê ëèñò, ò.å. êîíåö ñëîâà
    node->isEndOfWord = true;
}

// Âîçâðàøàåò true åñëè êëþ÷ åñòü â äåðåâå, èíà÷å false 
bool search(struct TrieNode* root, string key)
{
    struct TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

// Âîõâðàùàåò true åñëè root èìååò ëèñò, èíà÷å false 
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

TrieNode* wordjump(TrieNode* root, string key)
{
    for (int i = 0; i < key.length(); i++)
    {
        root = root->children[static_cast<int>(key[i] - 'a')]; 
    }
    return root;
}

// Ðåêóðñèâíàÿ ôóíêöèÿ óäàëåíèÿ êëþ÷à èç äåðåâà 
TrieNode* remove(TrieNode* root, string key, int depth)
{
    // Åñëè äåðåâî ïóñòîå 
    if (!root)
        return nullptr;
    root->freq--;
    // åñëè äîøëè äî êîíöà êëþ÷à 
    if (depth == key.size()) {

        // Ýòîò óçåë áîëüøå íå êîíåö ñëîâà 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // Åñëè êëþ÷ íå åâëÿåòñÿ ïðåôèêñîì, óäàëÿåì åãî
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // Åñëè íå äîøëè äî êîíöà êëþ÷à, ðåêóðñèâíî âûçûâàåì äëÿ ðåáåíêà 
    // ñîîòâåòñòâóþùåãî ñèìâîëà 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // Åñëè ó êîðíÿ íåò äî÷åðíåãî ñëîâà 
    // (óäàëåí òîëüêî îäèí åãî äî÷åðíèé ýëåìåíò), 
    // è îí íå çàêàí÷èâàåòñÿ äðóãèì ñëîâîì. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }

    // âîçâðàùàåì íîâûé êîðåíü
    return root;
}


// íå èçìåíèÿéòå ñèãíàòóðó ôóíêöèè
void findMinPrefixes(TrieNode* root, char buf[], int ind, string& res)
{
    if (!root)
        return;
    if (root->freq <= 1 )
    {
        buf[ind] = '\0';
        res += (string)buf + ' ';
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (root->children[i] != nullptr)
        {
            buf[ind] = i + 'a';
            findMinPrefixes(root->children[i], buf, ind + 1, res);
        }
    }
 //   std::cout << res << " ";
}
void findWords(TrieNode* root, char buf[], int ind, string& res)
{
    if (!root)
        return;
    if (root->isEndOfWord)
    {
        buf[ind] = '\0';
        res += (string)buf + ' ';
    }
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (root->children[i] != nullptr)
        {
            buf[ind] = i + 'a';
            findWords(root->children[i], buf, ind + 1, res);
        }
    }
    //   std::cout << res << " ";
}
