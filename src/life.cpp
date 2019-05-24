#include "../include/life.hpp"

void Life::reset( void )
{
    // Remember to adjust the virtual size to real dimensions.
    m_grid.resize( m_rows * m_cols );
    // Set all the position with dead cells 
    m_grid.assign( m_grid.size(), false);
}

void Life::update( void )
{
    grid_t past_gen = m_grid;

    for (auto x{0u}; x < rows(); x++)
        for (auto y{0u}; y < cols(); y++)
        {
            if ( past_gen[y * cols() + x] )
            {
                m_curr_generation.push_back(Point2(x, y));
            }
            past_gen[y * cols() + x] = rule(neighbors(m_grid, Point2(x, y)), m_grid[y * cols() + x]);
        }
    m_grid.swap(past_gen);
    updateLog(m_curr_generation);
}

void Life::updateLog( log_t &curr_gen )
{
    m_log.push_back( curr_gen );
    curr_gen.clear();
}

void Life::print( void )
{
    for ( auto x{0u}; x < rows(); x++ )
        for ( auto y{0u}; y < cols(); y++ )
        {
            if ( y == 0 ) { std::cout << "    ["; }
            if ( m_grid[ y * cols() + x ] )
            {
                std::cout << l_cell();
            }
            else
            {
                std::cout << d_cell();
            }
            if ( y == cols() - 1 ) { std::cout << "]" << std::endl; }
        }
}

void Life::print_file( libs::File& f )
{
    for ( auto x{0u}; x < rows(); x++ )
        for ( auto y{0u}; y < cols(); y++ )
        {
            if ( y == 0) { f.write_file(" ["); }
            if ( m_grid[y * cols() + x] )
            {
                f.write_file(l_cell());
            } else {
                f.write_file(d_cell());
            }
            if (y == cols() - 1) { f.write_file("]\n"); }
        }
}

void Life::welcome_message( void )
{
    std::cout << std::endl;
    std::cout << std::setfill ('*') << std::setw(74) << "*" << std::endl;
    std::cout << "\t\t   Welcome to Conway’s game of Life." << std::endl;
    std::cout << "\tRunning a simulation on a grid of size " << rows() << " by " 
              << cols() << " in which" << std::endl;
    std::cout << "\teach cell can either be occupied by an organism or not." << std::endl;
    std::cout << "\tThe occupied cells change from generation to generation" << std::endl; 
    std::cout << "\taccording to the number of neighboring cells which are alive." << std::endl;
    std::cout << std::setfill ('*') << std::setw(75) << "*" << std::endl;
}

void Life::set_cell_position ( const Point2 &p )
{
    if(p.x >= (long)rows() or p.y >= (long)cols())
        return;
    m_grid[ p.y * cols() + p.x ] = true;
}

void Life::set_rule( int born, int min_survive, int max_survive )
{
    born_rule = born;
    survive_rule[0] = min_survive;
    survive_rule[1] = max_survive;
}

int Life::neighbors(const grid_t &grid, const Point2 &p )
{
    int living_neighbors{0};

    for(auto i=-1; i < 2; i++)
        for(auto j=-1; j < 2; j++)
            if (!((p.x + i) < 0 or (p.y + j < 0)))
                if ( grid[ (p.y + j) * cols() + (p.x + i) ] )
                    if (!( i == 0 and j == 0)) 
                        living_neighbors++;
    return living_neighbors;
}

bool Life::rule( int qnt_neighbors, bool LoD )
{
    bool cell_state = LoD;
    
    if ( qnt_neighbors == born_rule)
        cell_state = true;
    else if ( qnt_neighbors < survive_rule[0])
        cell_state = false;
    else if ( qnt_neighbors > survive_rule[1])
        cell_state = false;

    return cell_state;
}

bool Life::extinct( void )
{
    bool is_extinct{true};

    for (size_t i{0}; i < m_grid.size(); i++)
    {
        if ( m_grid[i] )
        {
            is_extinct=false;
            break;
        }
    }
    
    return is_extinct; 
}

bool Life::stable( void )
{
    bool is_stable{false};

    if ( m_log.size() > 1 )
        for (size_t i=0; i < m_log.size(); i++)
            if ( m_log.back() == m_log[i-1] )
                    is_stable=true;
    return is_stable;
}