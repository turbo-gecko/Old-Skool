program SetPort;

var Error, PortNumber, OutValue: Integer;
var PortStr, ValueStr: String[3];

procedure OutPort(Port: Byte; Value: Byte);
begin
  inline ($3A/Port/       {      ld a,Port     }
          $4F/            {      ld c,a        }
          $3A/Value/      {      ld a,(Value)  }
          $ED/$79         {      out (c),a     });
end;

procedure ErrorAndExit(ErrorCode: Integer);
begin
  writeln('An error has occured. Error code is ', ErrorCode);
  exit;
end;

begin
  if ParamCount = 2 then
    begin
      PortStr := ParamStr(1);
      ValueStr := ParamStr(2);
      val(PortStr, PortNumber, Error);
      if Error <> 0 then
        ErrorAndExit(Error);
      val(ValueStr, OutValue, Error);
      if Error <> 0 then
        ErrorAndExit(Error);
    end
  else
    begin
      writeln('Output byte to a port');

      write('Port number > ');
      readln(PortNumber);

      write('Output value > ');
      readln(OutValue);
    end;

  OutPort(PortNumber, OutValue);
end.

