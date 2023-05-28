#include "map.h"

void CMap::readMap ( std::string & mapDir )
{
  std::ifstream ifs ( mapDir, std::ios::in );
  char c;
  // Reading height and width of map that are given in format 'hh ww\n' on the first line.
  // Max width and max height = 99;
  ifs . get ( c );
  m_Height += ( ( ( int ) c ) - 48 ) * 10;
  ifs . get ( c );
  m_Height += ( ( ( int ) c ) - 48 );
  ifs . get ( c );
  ifs . get ( c );
  m_Width += ( ( ( int ) c ) - 48 ) * 10;
  ifs . get ( c );
  m_Width += ( ( ( int ) c ) - 48 );
  ifs . get ( c );
  ifs . get ( c );
  m_Round += ( ( ( int ) c ) - 48 ) * 10;
  ifs . get ( c );
  m_Round += ( ( ( int ) c ) - 48 );
  ifs . get ( c );

  std::vector<std::vector< std::pair <char, bool> > > map( m_Height, std::vector< std::pair <char, bool> >( m_Width ) );

  for ( int i = 0; i < m_Height; ++i )
  {
    for ( int j = 0; j < m_Width; ++j )
    {
      ifs . get( c );
      map [i][j] . first = c;
      map [i][j] . second = false;
    }
    ifs . get( c );
  }
  ifs . close();

  for ( int i = 0; i < m_Height; ++i )
    for ( int j = 0; j < m_Width; ++j )
      if ( !map[i][j] . second )
        switch ( map[i][j] . first )
        {
          case '#':
            m_ElementList . push_back ( new CWall( CCoords ( j, i ) ) );
            map[i][j] . second = true;
            break;
          case ' ':
            m_ElementList . push_back ( new CVoid( CCoords ( j, i ) ) );
            map[i][j] . second = true;
            break;
          case '*':
            for ( int k = 0; k < 5; k++ )
              for ( int k1 = 0; k1 < 3; k1++ )
                map[i + k1][j + k] . second = true;
            m_AntHill . push_back ( new CAntHill( CCoords ( j, i ),
                                          map[i+1][j+1] . first,
                                          (int)(map[i+1][j+2] . first - 48) * 10 + (int)(map[i+1][j+3] . first - 48),
                                          map[i+1][j] . first - 48 ) );
           if ( map[i+1][j+1] . first == 'g' )
              m_Players . insert ( std::make_pair( map[i+1][j+1] . first, (int)(map[i+2][j+1] . first - 48) * 100
                                                                        + (int)(map[i+2][j+2] . first - 48) * 10
                                                                        + (int)(map[i+2][j+3] . first - 48) ) );
            else if ( map[i+1][j+1] . first != 'g' )
              m_Players . insert ( std::make_pair( map[i+1][j+1] . first, (int)(map[i+2][j+1] . first - 48) * 100
                                                                        + (int)(map[i+2][j+2] . first - 48) * 10
                                                                        + (int)(map[i+2][j+3] . first - 48) ) );
            break;
          default:
            break;
        }

  for ( const auto & it : m_AntHill )
    for ( const auto & it1 : m_AntHill )
      if ( it != it1 )
        createRoad( it -> getId(), it1 -> getId(), map );
  

  
}  
  
void CMap::print ( void )
{
  m_Screen -> screenClear();
  m_Screen -> screenRefresh();
  for ( const auto & it : m_ElementList )
    it -> print ( m_Screen );
  for ( const auto & it : m_AntHill )
    it -> print ( m_Screen );
  m_Screen -> screenRefresh();
}

int CMap::getAntHill ( CCoords coord )
{
  for ( const auto & it : m_AntHill )
    if ( it -> isInside ( coord ) )
      return it -> getId();
  return -1;
}

void CMap::add ( int id, int amount )
{
  for ( const auto & it : m_AntHill )
    if ( it -> getId() == id )
      it -> add ( amount );
}

int CMap::getAntsOfId ( int id )
{
  for ( const auto & it : m_AntHill )
    if (  it -> getId() == id )
      return it -> getAnts();
  return -1;
}

void CMap::setAntsOfId ( int id, int amount )
{
  for ( const auto & it : m_AntHill )
    if (  it -> getId() == id )
      it -> setAnts( amount );
}

int CMap::getAttackOfId ( int id )
{
  for ( const auto & it : m_AntHill )
    if (  it -> getId() == id )
      return it -> getAttack();
  return -1;
}

int CMap::getArmorOfId ( int id )
{
  for ( const auto & it : m_AntHill )
    if (  it -> getId() == id )
      return it -> getArmor();
  return -1;
}


char CMap::getColorOfId ( int id )
{
  for ( const auto & it : m_AntHill )
    if (  it -> getId() == id )
      return it -> getColor();
  return 'n';
}

CCoords CMap::getCoordsOfId ( int id )
{
  for ( const auto & it : m_AntHill )
    if (  it -> getId() == id )
      return it -> getCoords();
  return CCoords ( -1, -1 );
}

void CMap::setColorOfId ( int id, char color )
{
  for ( const auto & it : m_AntHill )
    if (  it -> getId() == id )
      return it -> setColor( color );
}

CAntHill * CMap::getAntHillOfId ( int id )
{
  for ( const auto & it : m_AntHill )
    if (  it -> getId() == id )
      return it;
  return nullptr;
}

void CMap::createAnts ( void )
{
  for ( const auto & it : m_AntHill )
    if ( it -> getColor() != 'w' )
      it -> createAnts();
}

char CMap::checkWinner ( void )
{
  char c = m_AntHill . front() -> getColor();
  for ( const auto & it : m_AntHill )
    if ( it -> getColor() != c )
      return 'n';
  return c; 
}

int CMap::getStrongest ( char c )
{
  int max = -1, id = -1;
  for ( const auto & it : m_AntHill )
    if ( it -> getColor() == c
      && it -> getAnts() > max )
    {
      max = it -> getAnts();
      id = it -> getId();
    }
  return id;
}

int CMap::getWeakest ( char c )
{
  int max = 1000, id = -1;
  for ( const auto & it : m_AntHill )
    if ( it -> getColor() != c
      && it -> getAnts() < max )
    {
      max = it -> getAnts();
      id = it -> getId();
    }
  return id;
}

void CMap::clearRoads ( void )
{
  for ( auto & it : m_Roads )
    it . clearRoad();
} 

void CMap::fillRoad ( const int from, const int to )
{
  for ( auto & it : m_Roads )
    if ( it . m_First == from && it . m_Second == to )
    {
      it . m_VecAnts[ it . m_VecAnts . size() - 1 ] . first = getAttackOfId( from ); 
      it . m_VecAnts[ it . m_VecAnts . size() - 1 ] . second = getColorOfId( from );
      it . m_FirstUsed = true;
      add ( from, - getAttackOfId( from ) );
      print();
    }
    else if ( it . m_First == to && it . m_Second == from )
    {
      it . m_VecAnts[ 0 ] . first = getAttackOfId( from );
      it . m_VecAnts[ 0 ] . second = getColorOfId( from );
      it . m_SecondUsed = true;
      add ( from, - getAttackOfId( from ) );
      print();
    }
}

void CMap::attack ( void )
{
  for ( auto & main_it : m_Roads )
  {  
    if ( !main_it . m_FirstUsed && !main_it . m_SecondUsed )
      continue;    
    if ( main_it . m_SecondUsed && main_it . m_VecAnts[ 0 ] . second != getColorOfId ( main_it . m_Second ) )
      continue;    
    if ( main_it . m_FirstUsed && main_it . m_VecAnts[ main_it . m_VecAnts . size() - 1 ] . second != getColorOfId ( main_it . m_First ) )
      continue;    

    for ( size_t i = 0; i < main_it . m_VecAnts . size() - 1; ++i )
    {
      if ( main_it . m_FirstUsed )
      {
        if ( main_it . m_VecAnts[ main_it . m_VecAnts . size() - 2 - i ] . first != 0 )
        {
          if ( main_it . m_VecAnts[ main_it . m_VecAnts . size() - 2 - i ] . first == main_it . m_VecAnts[ main_it . m_VecAnts . size() - 1 - i ] . first )
          {
            main_it . m_VecAnts[ main_it . m_VecAnts . size() - 2 - i ] . first = 0;
            main_it . m_FirstUsed = false;
            main_it . m_SecondUsed = false;
            break;
          }
          else if ( main_it . m_VecAnts[ main_it . m_VecAnts . size() - 2 - i ] . first > main_it . m_VecAnts[ main_it . m_VecAnts . size() - 1 - i ] . first )
          {
            main_it . m_VecAnts[ main_it . m_VecAnts . size() - 2 - i ] . first -= main_it . m_VecAnts[ main_it . m_VecAnts . size() - 1 - i ] . first;
            main_it . m_FirstUsed = false;
            main_it . m_VecAnts[ main_it . m_VecAnts . size() - 1 - i ] . first = 0;
            main_it . m_VecAnts[ main_it . m_VecAnts . size() - 1 - i ] . second = 'n';
          }
          else if ( main_it . m_VecAnts[ main_it . m_VecAnts . size() - 2 - i ] . first < main_it . m_VecAnts[ main_it . m_VecAnts . size() - 1 - i ] . first )
          {
            main_it . m_VecAnts[ main_it . m_VecAnts . size() - 2 - i ] . first = main_it . m_VecAnts[ main_it . m_VecAnts . size() - 1 - i ] . first - main_it . m_VecAnts[ main_it . m_VecAnts . size() - 2 - i ] . first;
            main_it . m_VecAnts[ main_it . m_VecAnts . size() - 2 - i ] . second = main_it . m_VecAnts[ main_it . m_VecAnts . size() - 1 - i ] . second;
            main_it . m_SecondUsed = false;
            main_it . m_VecAnts[ main_it . m_VecAnts . size() - 1 - i ] . first = 0;
            main_it . m_VecAnts[ main_it . m_VecAnts . size() - 1 - i ] . second = 'n';
          }
        }
        else 
        {
          main_it . m_VecAnts[ main_it . m_VecAnts . size() - 2 - i ] . first  = main_it . m_VecAnts[ main_it . m_VecAnts . size() - 1 - i ] . first;
          main_it . m_VecAnts[ main_it . m_VecAnts . size() - 2 - i ] . second = main_it . m_VecAnts[ main_it . m_VecAnts . size() - 1 - i ] . second;
          main_it . m_VecAnts[ main_it . m_VecAnts . size() - 1 - i ] . first = 0;
          main_it . m_VecAnts[ main_it . m_VecAnts . size() - 1 - i ] . second = 'n';
          if ( i == main_it . m_VecAnts . size() - 2 )
          {
            if ( getColorOfId ( main_it . m_First ) == getColorOfId ( main_it . m_Second ) )
              add ( main_it . m_Second, main_it . m_VecAnts[ 0 ] . first );
            else
            {
              add ( main_it . m_Second, -main_it . m_VecAnts[ 0 ] . first  );
              if ( getAntsOfId ( main_it . m_Second ) == 0 )
                setColorOfId ( main_it . m_Second, 'w' );
            }
            if ( getAntsOfId ( main_it . m_Second ) < 0 )
            {
              setColorOfId( main_it . m_Second, getColorOfId ( main_it . m_First ) );
              setAntsOfId( main_it . m_Second, getAntsOfId( main_it . m_Second ) * (-1) );
            }
          }
        }
      }
      if ( main_it . m_SecondUsed )
      {
        if ( main_it . m_VecAnts[ i + 1 ] . first != 0 )
        {
          if ( main_it . m_VecAnts[ i + 1 ] . first == main_it . m_VecAnts[ i ] . first )
          {
            main_it . m_VecAnts[ i + 1 ] . first = 0;
            main_it . m_VecAnts[ i ] . first = 0;
            main_it . m_VecAnts[ i ] . second = 'n';
            main_it . m_FirstUsed = false;
            main_it . m_SecondUsed = false;
            break;
          }
          else if ( main_it . m_VecAnts[ i + 1 ] . first > main_it . m_VecAnts[ i ] . first )
          {
            main_it . m_VecAnts[ i + 1 ] . first -= main_it . m_VecAnts[ i ] . first;
            main_it . m_SecondUsed = false;
            main_it . m_VecAnts[ i ] . first = 0;
            main_it . m_VecAnts[ i ] . second = 'n';
          }
          else if ( main_it . m_VecAnts[ i + 1 ] . first < main_it . m_VecAnts[ i ] . first )
          {
            main_it . m_VecAnts[ i + 1 ] . first = main_it . m_VecAnts[ i ] . first - main_it . m_VecAnts[ i + 1 ] . first;
            main_it . m_VecAnts[ i + 1 ] . second = main_it . m_VecAnts[ i ] . second;
            main_it . m_FirstUsed = false;
            main_it . m_VecAnts[ i ] . first = 0;
            main_it . m_VecAnts[ i ] . second = 'n';
          }
        }
        else
        {
          main_it . m_VecAnts[ i + 1 ] . first  = main_it . m_VecAnts[ i ] . first;
          main_it . m_VecAnts[ i + 1 ] . second = main_it . m_VecAnts[ i ] . second;
          main_it . m_VecAnts[ i ] . first = 0;
          main_it . m_VecAnts[ i ] . second = 'n';
          if ( i == main_it . m_VecAnts . size() - 2 )
          {
            if ( getColorOfId ( main_it . m_First ) == getColorOfId ( main_it . m_Second ) )
              add ( main_it . m_First, main_it . m_VecAnts[ main_it . m_VecAnts . size() - 1 ] . first  );
            else
            {
              add ( main_it . m_First, -main_it . m_VecAnts[ main_it . m_VecAnts . size() - 1 ] . first  );
              if ( getAntsOfId ( main_it . m_First ) == 0 )
                setColorOfId ( main_it . m_First, 'w' );
            }
            if ( getAntsOfId ( main_it . m_First ) < 0 )
            {
              setColorOfId( main_it . m_First, getColorOfId ( main_it . m_Second ) );
              setAntsOfId( main_it . m_First, getAntsOfId( main_it . m_First ) * (-1) );
            }
          }
        }
      }
      main_it . print( m_Screen );
      wrefresh ( m_Screen -> m_Window );
      std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    }
    print();
  }
}

int CMap::countHills ( char c )
{
  int i = 0;
  for ( const auto & it : m_AntHill )
    if ( it -> getColor() == c )
      i++;
  return i;
}

void CMap::createRoad( int from,
                       int to, 
                       std::vector<std::vector< std::pair <char, bool> > > & map )
{
  m_Screen -> screenClear();
  m_Screen -> screenRefresh();
  mvwprintw ( m_Screen -> m_Window, 0, 0, "Calculating a road between %d and %d ahthills...", from, to );
  wrefresh( m_Screen -> m_Window );
  for ( const auto & it : m_Roads )
    if ( ( it . m_First == from && it . m_Second == to )
      || ( it . m_First == to && it . m_Second == from ) )
        return; 
  std::map < CCoords, CCoords > way;
  std::queue < CCoords > q;
  CRoad road ( from, to );
  CCoords firstCoords = getCoordsOfId ( from );
  CCoords secondCoords = getCoordsOfId ( to );
  CAntHill * firstAh = getAntHillOfId ( from );
  CAntHill * secondAh = getAntHillOfId ( to );

  for ( int i = 0; i < m_Height; ++i )
    for ( int j = 0; j < m_Width; ++j )
      if ( map[i][j] . first == ' ' )
        map[i][j] . second = false;
      else
        map[i][j] . second = true;

  for ( int i = 0; i < 3; i++ )
    for ( int j = 0; j < 5; j++ )
    {  
      map[ firstCoords . m_Y + i ][ firstCoords . m_X + j ] . second = false;
      map[ secondCoords . m_Y + i ][ secondCoords . m_X + j ] . second = false;
    }
    
  firstCoords . m_X += 2;
  firstCoords . m_Y += 1;
  secondCoords . m_X += 2;
  secondCoords . m_Y += 1;

  q . push ( firstCoords );
  // int i = 0;
  while ( !q . empty() )
  {
    // mvwprintw ( m_Screen -> m_Window, 10, 55, "%d", q . size() );
    // for ( int i = 0; i < m_Height; i++ )
    //   for ( int j = 0; j < m_Width; j++ )
    //     mvwprintw ( m_Screen -> m_Window, i, j, "%d", map[ i ][ j ] . second );
    // wrefresh ( m_Screen -> m_Window );
    CCoords newCoords = q . front ();
    q . pop();

    if ( newCoords == secondCoords )
      break;

    if ( map[ newCoords . m_Y - 1 ][ newCoords . m_X ] . second == false )
    {
      q . push ( CCoords( newCoords . m_X, newCoords . m_Y - 1 ) );
      map[ newCoords . m_Y - 1 ][ newCoords . m_X ] . second = true;
      way . insert ( std::make_pair ( CCoords( newCoords . m_X, newCoords . m_Y - 1 ), newCoords ) );
    }
    if ( map[ newCoords . m_Y + 1 ][ newCoords . m_X ] . second == false )
    {
      q . push ( CCoords( newCoords . m_X, newCoords . m_Y + 1 ) );
      map[ newCoords . m_Y + 1 ][ newCoords . m_X ] . second = true;
      way . insert ( std::make_pair ( CCoords( newCoords . m_X, newCoords . m_Y + 1 ), newCoords ) );
    }
    if ( map[ newCoords . m_Y ][ newCoords . m_X + 1 ] . second == false )
    {
      q . push ( CCoords( newCoords . m_X + 1, newCoords . m_Y ) );
      map[ newCoords . m_Y ][ newCoords . m_X  + 1] . second = true;
      way . insert ( std::make_pair ( CCoords( newCoords . m_X + 1, newCoords . m_Y ), newCoords ) );
    }
    if ( map[ newCoords . m_Y ][ newCoords . m_X - 1 ] . second == false )
    {
      q . push ( CCoords( newCoords . m_X - 1, newCoords . m_Y ) );
      map[ newCoords . m_Y ][ newCoords . m_X - 1 ] . second = true;
      way . insert ( std::make_pair ( CCoords( newCoords . m_X - 1, newCoords . m_Y ), newCoords ) );
    }
  }

  road . m_Exists = q . empty() ? false : true;
  
  CCoords newCoords = secondCoords;
  if ( road . m_Exists == true )
    while ( newCoords != firstCoords )
    {
      std::pair < CCoords, CCoords > c = (* way . find ( newCoords ) );
      newCoords = c . second;
      if ( !firstAh -> isInside ( c . first )
        && !secondAh -> isInside ( c . first ) )
        road . m_Vec . push_back ( c . first );
    }
  for ( size_t i = 0; i < road . m_Vec . size(); ++i )
    road . m_VecAnts . push_back ( std::make_pair ( 0, 'n' ) );
  m_Roads . push_back ( road );
}

void CMap::addAntsAttackToColor ( char c, int amount )
{
  for ( const auto & it : m_AntHill )
    if ( it -> getColor() == c )
      it -> addAttack ( amount );
}

void CMap::addArmorToColor ( char c, int amount )
{
  for ( const auto & it : m_AntHill )
    if ( it -> getColor() == c )
      it -> addArmor ( amount );
}

void CMap::addMoveToColor ( char c, int amount )
{
  for ( const auto & it : m_AntHill )
    if ( it -> getColor() == c )
      it -> addMove ( amount );
}

void CMap::addMaxToColor ( char c, int amount )
{
  for ( const auto & it : m_AntHill )
    if ( it -> getColor() == c )
      it -> addMax ( amount );
}

void CMap::deactivateAll ( void )
{
  for ( const auto & it : m_AntHill )
    it -> clearAntHill();
}