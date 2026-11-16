#include <bits/stdc++.h>
using namespace std;

using Clock = chrono::high_resolution_clock;

/* =========================================================
   Quick Sort  (Median-of-Three pivot)
   ========================================================= */
long long qsortCmp = 0;
long long qsortMoves = 0;

void quickSortRec(vector<int>& a, int lo, int hi) {
    if (lo >= hi) return;

    int mid = lo + (hi - lo) / 2;

    // 세 값 a[lo], a[mid], a[hi] 정렬 (비교 + swap 이동 카운트)
    qsortCmp++;
    if (a[lo] > a[mid]) { swap(a[lo], a[mid]); qsortMoves += 3; }
    qsortCmp++;
    if (a[mid] > a[hi]) { swap(a[mid], a[hi]); qsortMoves += 3; }
    qsortCmp++;
    if (a[lo] > a[mid]) { swap(a[lo], a[mid]); qsortMoves += 3; }

    // a[mid] 가 중앙값 → pivot 위치 a[lo] 로
    swap(a[lo], a[mid]);
    qsortMoves += 3;

    int pivot = a[lo];
    int i = lo + 1;

    for (int j = lo + 1; j <= hi; ++j) {
        qsortCmp++;
        if (a[j] < pivot) {
            if (i != j) {
                swap(a[i], a[j]);
                qsortMoves += 3;
            }
            ++i;
        }
    }

    swap(a[lo], a[i - 1]);
    qsortMoves += 3;

    int p = i - 1;
    quickSortRec(a, lo, p - 1);
    quickSortRec(a, p + 1, hi);
}

void quickSort(vector<int>& a) {
    quickSortRec(a, 0, (int)a.size() - 1);
}

/* =========================================================
   Array-based Insert / Delete (sorted vector)
   ========================================================= */
long long arrCmp = 0;
long long arrMoves = 0;
int arrMaxSize = 0;

void arrayInsert(vector<int>& a, int value) {
    int n = (int)a.size();
    int pos = 0;

    // 삽입 위치 선형 탐색
    while (pos < n) {
        arrCmp++;
        if (a[pos] >= value) break;
        ++pos;
    }

    a.resize(n + 1);
    for (int i = n; i > pos; --i) {
        a[i] = a[i - 1];
        ++arrMoves;
    }
    a[pos] = value;
    ++arrMoves;

    if ((int)a.size() > arrMaxSize) arrMaxSize = (int)a.size();
}

bool arrayDelete(vector<int>& a, int value) {
    int n = (int)a.size();
    int pos = -1;

    // 삭제 대상 선형 탐색
    for (int i = 0; i < n; ++i) {
        arrCmp++;
        if (a[i] == value) { pos = i; break; }
    }
    if (pos < 0) return false;

    for (int i = pos; i < n - 1; ++i) {
        a[i] = a[i + 1];
        ++arrMoves;
    }
    a.pop_back();
    return true;
}

/* =========================================================
   AVL Tree (duplicate via count field)
   ========================================================= */
struct AVLNode {
    int key;
    int count;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(int k) : key(k), count(1), height(1), left(nullptr), right(nullptr) {}
};

long long avlCmp = 0;
long long avlMoves = 0;
long long avlNodeCount = 0;
long long avlMaxNodes = 0;

int H(AVLNode* n) { return n ? n->height : 0; }
void updH(AVLNode* n) { n->height = 1 + max(H(n->left), H(n->right)); }
int BF(AVLNode* n) { return n ? H(n->left) - H(n->right) : 0; }

AVLNode* rotRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updH(y);
    updH(x);
    return x;
}

AVLNode* rotLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updH(x);
    updH(y);
    return y;
}

AVLNode* rebalance(AVLNode* n) {
    updH(n);
    int b = BF(n);
    if (b > 1) {
        if (BF(n->left) < 0) n->left = rotLeft(n->left);
        return rotRight(n);
    }
    if (b < -1) {
        if (BF(n->right) > 0) n->right = rotRight(n->right);
        return rotLeft(n);
    }
    return n;
}

AVLNode* avlInsert(AVLNode* n, int key) {
    if (!n) {
        ++avlNodeCount;
        if (avlNodeCount > avlMaxNodes) avlMaxNodes = avlNodeCount;
        ++avlMoves;                 // key 값을 새 노드에 복사
        return new AVLNode(key);
    }

    avlCmp++;
    if (key < n->key) {
        n->left = avlInsert(n->left, key);
    } else {
        avlCmp++;
        if (key > n->key) {
            n->right = avlInsert(n->right, key);
        } else {
            ++n->count;
            ++avlMoves;             // count 증가
            return n;
        }
    }
    return rebalance(n);
}

AVLNode* findMin(AVLNode* n) {
    while (n->left) n = n->left;
    return n;
}

AVLNode* removeMin(AVLNode* n) {
    if (!n->left) {
        AVLNode* child = n->right;
        delete n;
        --avlNodeCount;
        return child;
    }
    n->left = removeMin(n->left);
    return rebalance(n);
}

AVLNode* avlDelete(AVLNode* n, int key, bool& deleted) {
    if (!n) { deleted = false; return nullptr; }

    avlCmp++;
    if (key < n->key) {
        n->left = avlDelete(n->left, key, deleted);
        return deleted ? rebalance(n) : n;
    }
    avlCmp++;
    if (key > n->key) {
        n->right = avlDelete(n->right, key, deleted);
        return deleted ? rebalance(n) : n;
    }

    // key == n->key
    deleted = true;
    if (n->count > 1) {
        --n->count;
        ++avlMoves;
        return n;
    }

    if (!n->left || !n->right) {
        AVLNode* child = n->left ? n->left : n->right;
        delete n;
        --avlNodeCount;
        return child;
    }

    AVLNode* succ = findMin(n->right);
    n->key   = succ->key;
    n->count = succ->count;
    avlMoves += 2;
    n->right = removeMin(n->right);
    return rebalance(n);
}

void avlInorder(AVLNode* n, vector<int>& out) {
    if (!n) return;
    avlInorder(n->left, out);
    for (int i = 0; i < n->count; ++i) out.push_back(n->key);
    avlInorder(n->right, out);
}

void avlFree(AVLNode* n) {
    if (!n) return;
    avlFree(n->left);
    avlFree(n->right);
    delete n;
}

/* =========================================================
   Format helpers
   ========================================================= */
string fmtTime(double ms) {
    ostringstream o;
    o << fixed << setprecision(3) << ms << " ms";
    return o.str();
}

/* =========================================================
   main
   ========================================================= */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> sizes = {1000, 2000, 4000, 8000, 16000, 20000};

    for (int n : sizes) {
        int ops = n / 5;

        // --- 원본 데이터 ---
        mt19937 dataRng(20240514u + n);
        uniform_int_distribution<int> dataDist(0, 1000000);
        vector<int> original(n);
        for (int& x : original) x = dataDist(dataRng);

        // --- 삽입/삭제 연산 시퀀스 (양쪽 공통) ---
        struct Op { bool isInsert; int value; };
        vector<Op> opList;
        opList.reserve(ops);

        mt19937 opRng(54321u + n);
        uniform_int_distribution<int> coin(0, 1);
        uniform_int_distribution<int> valDist(0, 1000000);

        for (int i = 0; i < ops; ++i) {
            bool isIns = (coin(opRng) == 0);
            int v = valDist(opRng);
            opList.push_back({isIns, v});
        }

        /* =================================================
           (A) Quick Sort + 배열 삽입/삭제
           ================================================= */
        vector<int> arr = original;
        qsortCmp = qsortMoves = 0;
        arrCmp = arrMoves = 0;
        arrMaxSize = (int)arr.size();

        auto t0 = Clock::now();

        quickSort(arr);
        for (auto& op : opList) {
            if (op.isInsert) arrayInsert(arr, op.value);
            else             arrayDelete(arr, op.value);
        }

        auto t1 = Clock::now();
        double quickTimeMs = chrono::duration<double, milli>(t1 - t0).count();

        long long quickTotalCmp   = qsortCmp + arrCmp;
        long long quickTotalMoves = qsortMoves + arrMoves;
        size_t    quickMem        = (size_t)arrMaxSize * sizeof(int) + 2048; // +2KB recursion
        int       quickFinal      = (int)arr.size();

        /* =================================================
           (B) AVL Tree Sort + AVL 삽입/삭제
           ================================================= */
        avlCmp = avlMoves = 0;
        avlNodeCount = 0;
        avlMaxNodes = 0;
        AVLNode* root = nullptr;

        auto t2 = Clock::now();

        for (int v : original) root = avlInsert(root, v);
        for (auto& op : opList) {
            if (op.isInsert) {
                root = avlInsert(root, op.value);
            } else {
                bool d;
                root = avlDelete(root, op.value, d);
            }
        }

        auto t3 = Clock::now();
        double avlTimeMs = chrono::duration<double, milli>(t3 - t2).count();

        long long avlTotalCmp   = avlCmp;
        long long avlTotalMoves = avlMoves;
        size_t    avlMem        = (size_t)avlMaxNodes * sizeof(AVLNode) + 2048; // +2KB recursion

        vector<int> avlOut;
        avlInorder(root, avlOut);
        int avlFinal = (int)avlOut.size();

        bool match = (quickFinal == avlFinal) && (arr == avlOut);

        /* =================================================
           출력
           ================================================= */
        cout << "Data Size : " << n << "\n";
        cout << "Operations: " << ops << "\n\n";

        cout << left  << setw(18) << ""
             << setw(16) << "Quick Sort"
             << setw(16) << "AVL Tree" << "\n";
        cout << string(50, '-') << "\n";

        cout << left  << setw(18) << "Total Time"
             << setw(16) << fmtTime(quickTimeMs)
             << setw(16) << fmtTime(avlTimeMs) << "\n";

        cout << left  << setw(18) << "Comparisons"
             << setw(16) << quickTotalCmp
             << setw(16) << avlTotalCmp << "\n";

        cout << left  << setw(18) << "Data Movements"
             << setw(16) << quickTotalMoves
             << setw(16) << avlTotalMoves << "\n";

        cout << left  << setw(18) << "Memory Usage"
             << setw(16) << (to_string(quickMem) + " B")
             << setw(16) << (to_string(avlMem)   + " B") << "\n";

        cout << "\n";
        cout << left  << setw(18) << "Final Data Count"
             << setw(16) << quickFinal
             << setw(16) << avlFinal;
        if (!match) cout << "  [MISMATCH]";
        cout << "\n\n";

        avlFree(root);
    }

    return 0;
}