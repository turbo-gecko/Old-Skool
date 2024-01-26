program Test;

var MyPort: Byte;
var MyValue: Byte;
var Delay: Integer;

procedure OutPort(Port: Byte; Value: Byte);
begin
  inline ($3A/Port/$4F/$3A/Value/$ED/$79);
end;

begin
  MyPort := $02;
  MyValue := $FF;

  write('Port number > ');
  readln(MyPort);

  while MyValue > 0 do
    begin
      OutPort(MyPort, MyValue);
      MyValue := MyValue - 1;
      Delay := 500;
      while Delay > 0 do
        begin
          Delay := Delay - 1;
        end;
    end;

  OutPort(MyPort, MyValue);
end.

