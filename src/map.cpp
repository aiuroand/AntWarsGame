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
            for ( int k = 0; k < 6; k++ )
              for ( int k1 = 0; k1 < 3; k1++ )
                map[i + k1][j + k] . second = true;
            m_AntHill . push_back ( new CAntHill( CCoords ( j, i ),
                                          map[i+1][j+2] . first,
                                          (int)(map[i+1][j+3] . first - 48) * 10 + (int)(map[i+1][j+4] . first - 48),
                                          map[i+1][j] . first - 48 ) );
            if ( map[i+1][j+2] . first == 'g' )
              m_Players . insert ( map[i+1][j+2] . first );
            else if ( map[i+1][j+2] . first != 'g' )
              m_Players . insert ( map[i+1][j+2] . first );
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

void CMap::attack ( const int from, const int to )
{
  for ( const auto & it : m_Roads )
    if (  ( ( it . m_First == from && it . m_Second == to )
         || ( it . m_First == to && it . m_Second == from ) )) 
    it . print( m_Screen );
    wrefresh ( m_Screen -> m_Window );
  std::this_thread::sleep_for( std::chrono::seconds( 2 ) );
  
  int f = getAttackOfId ( from );
  add ( from, -f );

  if ( getColorOfId ( to ) == getColorOfId ( from ) )
    add ( to, f );
  else
  {
    add ( to, -f );
    if ( getAttackOfId ( to ) == 0 )
      setColorOfId ( to, 'w' );
  }
  if ( getAntsOfId ( to ) < 0 )
  {
    setColorOfId( to, getColorOfId ( from ) );
    setAntsOfId( to, getAntsOfId( to ) * (-1) );
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
  for ( const auto & it : m_Roads )
    if ( ( it . m_First == from && it . m_Second == to )
      || ( it . m_First == to && it . m_Second == from ) )
        return;
  std::map < CCoords, CCoords > way;
  std::queue < CCoords > q;
  CRoad road ( from, to );
  CCoords firstCoords = getCoordsOfId ( from );
  CCoords secondCoords = getCoordsOfId ( to );

  q . push ( firstCoords );

  for ( int i = 0; i < m_Height; ++i )
    for ( int j = 0; j < m_Width; ++j )
      if ( map[i][j] . first == ' ' )
        map[i][j] . second = false;
      else
        map[i][j] . second = true;

  map[ firstCoords . m_Y ][ firstCoords . m_X ] . second = false;
  map[ secondCoords . m_Y ][ secondCoords . m_X ] . second = false;

  while ( !q . empty() )
  {
    CCoords newCoords = q . front ();
    q . pop();
    map[ newCoords . m_Y ][ newCoords . m_X ] . second = true;

    if ( newCoords == secondCoords )
      break;

    if ( map[ newCoords . m_Y - 1 ][ newCoords . m_X ] . second == false )
    {
      q . push ( CCoords( newCoords . m_X, newCoords . m_Y - 1 ) );
      way . insert ( std::make_pair ( CCoords( newCoords . m_X, newCoords . m_Y - 1 ), newCoords ) );
    }
    if ( map[ newCoords . m_Y + 1 ][ newCoords . m_X ] . second == false )
    {
      q . push ( CCoords( newCoords . m_X, newCoords . m_Y + 1 ) );
      way . insert ( std::make_pair ( CCoords( newCoords . m_X, newCoords . m_Y + 1 ), newCoords ) );
    }
    if ( map[ newCoords . m_Y ][ newCoords . m_X + 1 ] . second == false )
    {
      q . push ( CCoords( newCoords . m_X + 1, newCoords . m_Y ) );
      way . insert ( std::make_pair ( CCoords( newCoords . m_X + 1, newCoords . m_Y ), newCoords ) );
    }
    if ( map[ newCoords . m_Y ][ newCoords . m_X - 1 ] . second == false )
    {
      q . push ( CCoords( newCoords . m_X - 1, newCoords . m_Y ) );
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
      if ( c . first != secondCoords )
        road . m_Vec . push_back ( c . first );
    }

  m_Roads . push_back ( road );

}