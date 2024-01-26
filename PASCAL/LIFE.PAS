{ Conway's game of Life
  taken from J. S. Rohl's book Writing Pascal programs
  pp. 79-97 }

program Life;
const
  nrows = 21; nrows1 = 22;
  ncols = 50; ncols1 = 51;
  margin = '        ';
  margin2 = '   ';
type
  BigStr = String[255];
  rowrange = 1..nrows; xrowrange = 0..nrows1;
  colrange = 1..ncols; xcolrange = 0..ncols1;
  colonytype = array[rowrange, colrange] of (unoccupied, occupied);
var
  ConfFileName: BigStr;
  generation, ngenerations: Integer;
  colony: colonytype;
  state: (stillchanging, extinct, stable);

procedure GotoRowCol(row, col: Integer); {==================================}
var
  sR, sC: String[3];
begin
  Str(100+row, sR);
  Str(100+col, sC);
  write(chr(27)+'['+Copy(sR,2,2)+';'+Copy(sC,2,2)+'H');
end; { GotoRowCol }

procedure SetUpColony; {====================================================}
{ This procedure creates the initial state of the colony
  including the unoccupied surrounding ring from
  the data supplied. For ease of use the data is
  a rectangle around the centre of the colony in
  which all the organisms are found. The data is
  the depth and the width of the region followed
  by the region itself, in which a blank represents
  the absence of an organism and any other character
  its presence. }
var
  row: xrowrange;
  depth: rowrange;
  col: xcolrange;
  width: colrange;
  lRow: BigStr;
  lConfFile: Text;
  i: Integer;

begin { SetUpColony }
  assign(lConfFile, ConfFileName);
  Reset(lConfFile);
  Read(lConfFile, ngenerations, depth, width);
  generation := 1; state := stillchanging;
  for row := 1 to nrows do
    for col := 1 to ncols do
      colony[row,col] := unoccupied;
  for row := (nrows-depth) div 2 + 1 to (nrows+depth) div 2 do
  begin
    if eof(lConfFile) then
    begin
      writeln('EOF!');
      exit
    end;
    readln(lConfFile, lRow);
    col := (ncols-width) div 2 + 1;
    for i := 1 to Length(lRow) do
    begin
      if lRow[i] <> ' 'then
        colony[row,col] := occupied;
      col := col + 1
    end; { next i }
  end; { next row }
  Close(lConfFile);
end; { SetUpColony }


procedure DrawColony; {=====================================================}
const
  line = '-'; cross = '+'; vline = '|'; organism = '*'; noorganism = ' ';
var
  row: rowrange;
  col: colrange;

begin
  GotoRowCol(1, 1);
  write(margin2, 'G', generation:3, ' ');
  write (cross);
  for col := 1 to ncols do
    write(line);
  writeln(cross);
  for row := 1 to nrows do
  begin
    write(margin, vline);
    for col := 1 to ncols do
      if colony[row, col] = occupied then
        write(organism)
      else
        write(noorganism);
      writeln(vline)
  end; { next row }
  write(margin, cross);
  for col := 1 to ncols do
    write(line);
  write(cross)
end; { DrawColony }

procedure MoveToNextGeneration; {==========================================}
var
  oldcolony: colonytype;

  procedure TransformColony; {---------------------------------------------}
  { This produces the new generation of the colony from the given rules }
  type
    zerotoeight = 0..8;
  var
    row: rowrange;
    col: colrange;

    function Neighbours: zerotoeight; {....................................}
    { This function finds the number of neigbours (in the old colony)
      that the organism (if any) in cell[row, col] has }
    var
      n: 0..9;
      dr: xrowrange;
      dc: xcolrange;
    begin
      n := 0;
      for dr := row-1 to row+1 do
        for dc := col-1 to col+1 do
          n := n + ord(oldcolony[dr, dc]);
      Neighbours := n - ord(oldcolony[row, col])
    end; { Neighbours }

  begin { TransformColony }
    for row := 1 to nrows do
      for col := 1 to ncols do
        case Neighbours of
          0,1,4,5,6,7,8: colony[row, col] := unoccupied;
            2: ; { no change }
              3: colony[row, col] := occupied;
              end { case }
  end; { TransformColony }

  procedure TestForExtinction; {-------------------------------------------}
  label 1;
  var
    row: rowrange;
    col: colrange;
  begin
    for row := 1 to nrows do
      for col := 1 to ncols do
        if colony[row, col] = occupied then goto 1;
    state := extinct;
  1:
  end; { TestForExtinction } {---------------------------------------------}

  procedure TestForStability;  {-------------------------------------------}
  label 1;
  var
    row: rowrange;
    col: colrange;
  begin
    for row := 1 to nrows do
      for col := 1 to ncols do
        if colony[row, col] <> oldcolony[row, col] then goto 1;
    state := stable;
  1:
  end; { TestForStability; }

begin { MoveToNextGeneration }
  oldcolony := colony;
  TransformColony;
  generation := generation + 1;
  TestForExtinction;
  if state <> extinct then
    TestForStability
end; { MoveToNextGeneration }

function Finished: Boolean; {==============================================}
begin
  Finished := (generation = ngenerations) or (state <> stillchanging)
end; { Finished }

procedure WriteOutReason; {================================================}
begin
  writeln; writeln;
  if state = extinct then
    writeln(margin, 'The colony has become extinct.')
  else if state = stable then
    writeln(margin, 'The colony has achieved stability.')
  else
    writeln(margin, 'The simulation has now stopped.')
end; { WriteOutReason }

{==========================================================================}
begin { main }
  ConfFileName := 'LIFE.CFG';
  SetUpColony;
  ClrScr;
  DrawColony;
  repeat
    MoveToNextGeneration;
    DrawColony
  until Finished;
  WriteOutReason
end.
