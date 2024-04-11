// https://leetcode.com/problems/construct-quad-tree/?envType=study-plan-v2&envId=top-interview-150

/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/

class Solution {
    static constexpr inline const size_t pool_cap = 128 * 128;
    static inline array<Node, pool_cap> pool;
    static inline size_t pool_sz = 0;

    template<typename K>
    static inline void pp(K && k) {
        cout<<k;
        cout<<endl;
    }

    template<typename K, typename... T>
    static inline void pp(K && k, T && ...t) {
        cout<<k<<" ";
        pp(t...);
    }

    template<typename... T>
    static inline Node * allocate_node(const T && ...t) {
        if (pool_sz < pool_cap) {
            return new (&pool[pool_sz++]) Node(t...);
        }
        return new Node(t...);
    }

    class SqrPow2GridView {
        const vector<vector<int>>* pgrid;
        size_t top_left_row_;
        size_t top_left_col_;
        size_t length_of_sides_;

        constexpr SqrPow2GridView(const vector<vector<int>>& grid, const size_t top_left_row, const size_t top_left_col, const size_t length_of_sides): 
            pgrid{&grid}, top_left_row_{top_left_row}, top_left_col_{top_left_col}, length_of_sides_(length_of_sides)
            {}

    public:
        explicit constexpr SqrPow2GridView(const vector<vector<int>>& grid): 
            pgrid{&grid}, top_left_row_{0L}, top_left_col_{0L}, length_of_sides_(grid.size())
            {}

        void print() const {
            cout<<"GridView:"
                "\n\ttop_left_row="<<top_left_row_
                <<"\ttop_left_col="<<top_left_col_
                <<"\n\tlength_of_sides_="<<length_of_sides_
                <<"\n";

            const size_t end_row = length_of_sides_ + top_left_row_;
            const size_t end_col = length_of_sides_ + top_left_col_;
            for(size_t row = top_left_row_; row != end_row; ++row) {
                const auto &current_row = (*pgrid)[row];
                cout<< "\t|";
                for(size_t col = top_left_col_; col != end_col; ++col) {
                    cout<< " "<< current_row[col];
                }
                cout<< " |\n";
            }
            
        }

        constexpr bool empty() const {
            return !length_of_sides_;
        }

        constexpr bool isAllSame() const {
            const int val = (*pgrid)[top_left_row_][top_left_col_];
            
            const size_t end_row = length_of_sides_ + top_left_row_;
            const size_t end_col = length_of_sides_ + top_left_col_;
            for(size_t row = top_left_row_; row != end_row; ++row) {
                const auto &current_row = (*pgrid)[row];
                for(size_t col = top_left_col_; col != end_col; ++col) {
                    if (current_row[col] != val) return false;
                }
            }
            return true;
        }

        constexpr inline int get(size_t row, size_t col) const {
            return (*pgrid)[row + top_left_row_][col + top_left_col_];
        }

        constexpr inline int length_of_sides() const { return length_of_sides_; }

        constexpr inline SqrPow2GridView subView(const size_t top_left_row, const size_t top_left_col, const size_t length_of_sides) const {
            return SqrPow2GridView(
                *pgrid,
                top_left_row_ + top_left_row,
                top_left_col_ + top_left_col,
                length_of_sides
            );
        }
    };

    /**
        n == grid.length == grid[i].length
        n == 2^x where 0 <= x <= 6
     */
    static Node* construct(SqrPow2GridView grid_view) {
        if (grid_view.empty()) return nullptr;

        const size_t mid = grid_view.length_of_sides()>>1;
        if (!mid || grid_view.isAllSame()) return allocate_node(grid_view.get(0, 0), true);

        return allocate_node(false, false, 
            construct(grid_view.subView(0, 0, mid)),
            construct(grid_view.subView(0, mid, mid)),
            construct(grid_view.subView(mid, 0, mid)),
            construct(grid_view.subView(mid, mid, mid))
        );
    }

public:
    /**
        n == grid.length == grid[i].length
        n == 2^x where 0 <= x <= 6
     */
    static Node* construct(const vector<vector<int>>& grid) {
        return construct(SqrPow2GridView(grid));
    }
};

