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
    class GridView {
        const vector<vector<int>>* pgrid;
        size_t top_left_row_;
        size_t top_left_col_;
        size_t num_of_rows_;
        size_t num_of_cols_;

        constexpr GridView(const vector<vector<int>>& grid, const size_t top_left_row, const size_t top_left_col, const size_t num_of_rows,
                                const size_t num_of_cols): 
            pgrid{&grid}, top_left_row_{top_left_row}, top_left_col_{top_left_col},
            num_of_rows_(num_of_rows), num_of_cols_(num_of_cols)
            {}

    public:
        explicit constexpr GridView(const vector<vector<int>>& grid): 
            pgrid{&grid}, top_left_row_{0L}, top_left_col_{0L},
            num_of_rows_(grid.size()), num_of_cols_(grid[0L].size())
            {}

        void print() const {
            cout<<"GridView:"
                "\n\ttop_left_row="<<top_left_row_
                <<" top_left_col="<<top_left_col_
                <<"\n\tnum_of_rows="<<num_of_rows_
                <<" num_of_cols="<<num_of_cols_
                <<"\n";

            for(size_t row = 0L; row  < num_of_rows_; ++row) {
                cout<< "\t|";
                for(size_t col = 0L; col  < num_of_cols_; ++col) {
                    cout<< " "<< get(row, col);
                }
                cout<< " |\n";
            }
            
        }

        constexpr bool empty() const {
            return !num_of_rows_ || !num_of_cols_;
        }

        constexpr bool isAllSame() const {
            int val = (*pgrid)[top_left_row_][top_left_col_];
            
            const size_t num_of_rows = num_of_rows_ + top_left_row_;
            const size_t num_of_cols = num_of_cols_ + top_left_col_;
            for(size_t row = top_left_row_; row != num_of_rows; ++row) {
                for(size_t col = top_left_col_; col != num_of_cols; ++col) {
                    if ((*pgrid)[row][col] != val) return false;
                }
            }
            return true;
        }

        constexpr inline int get(size_t row, size_t col) const {
            return (*pgrid)[row + top_left_row_][col + top_left_col_];
        }

        constexpr inline int num_of_rows() const { return num_of_rows_; }
        constexpr inline int num_of_cols() const { return num_of_cols_; }

        constexpr optional<GridView> subView(const size_t top_left_row, const size_t top_left_col, const size_t num_of_rows,
                                             const size_t num_of_cols) const {
            const size_t top_left_row_local = top_left_row_ + top_left_row;
            const size_t top_left_col_local = top_left_col_ + top_left_col;

            if (num_of_rows + top_left_row > num_of_rows_ || num_of_cols + top_left_col > num_of_cols_) return {};

            return GridView(
                *pgrid,
                top_left_row_local,
                top_left_col_local,
                num_of_rows,
                num_of_cols
            );
        }

        constexpr optional<GridView> subView(const size_t top_left_row, const size_t top_left_col) const {
            const size_t top_left_row_local = top_left_row_ + top_left_row;
            const size_t top_left_col_local = top_left_col_ + top_left_col;

            if (top_left_row > num_of_rows_ || top_left_col > num_of_cols_) return {};

            return GridView(
                *pgrid,
                top_left_row_local,
                top_left_col_local,
                num_of_rows_ - top_left_row,
                num_of_cols_ - top_left_col
            );
        }
    };

    static inline Node* construct(optional<GridView> opt_grid_view) {
        return opt_grid_view ? construct(*opt_grid_view): nullptr;
    }

    /**
        n == grid.length == grid[i].length
        n == 2^x where 0 <= x <= 6
     */
    static Node* construct(GridView grid_view) {
        //grid_view.print();
        if (grid_view.empty()) return nullptr;

        if (grid_view.isAllSame()) return new Node(grid_view.get(0, 0), true);

        const size_t mid_row = grid_view.num_of_rows()>>1;
        const size_t mid_col = grid_view.num_of_cols()>>1;

        return new Node(false, false, 
            construct(grid_view.subView(0, 0, mid_row, mid_col)),
            construct(grid_view.subView(0, mid_col, mid_row, mid_col)),
            construct(grid_view.subView(mid_row, 0, mid_row, mid_col)),
            construct(grid_view.subView(mid_row, mid_col, mid_row, mid_col))
        );
    }

public:
    /**
        n == grid.length == grid[i].length
        n == 2^x where 0 <= x <= 6
     */
    static Node* construct(vector<vector<int>>& grid) {
        return construct(GridView(grid));
    }
};
