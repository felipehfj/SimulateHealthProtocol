#include <Arduino.h>

const char *ssid = "Acropole";
const char *password = "felipehfj";

const byte START_OF_BLOCK = 0x0b;
const byte END_OF_BLOCK = 0x1c;
const byte CARRIAGE_RETURN = 0x0d;
const byte LINE_FEED = 0x0a;

const char MSG01[] PROGMEM = "$1|SX072|20240320153613|-|Daniele|Chibally|Cao|vet D-dimer|DDTBB07V|2024.10.13|4955.29|||||ng/ml|-|-||||G|G|0|||||nome de gato|123|||VECTC100041";
const char MSG02[] PROGMEM = "$1|SX072|20240123153959|-||Teste|Cao|vet D-dimer|DDTBB07V|2024.10.13|326.08|||||ng/ml|-|-||||G|G|0|||||||||VECTC100041";
const char MSG03[] PROGMEM = "$1|SX072|20240123160119|-|||Cao|vet D-dimer|DDTBB07V|2024.10.13|142.87|||||ng/ml|-|-||||G|G|0|||||||||VECTC100041";
const char MSG04[] PROGMEM = "$1|SX072|20240227151337|-|Ale|Claus|Cao|SDMA|SDTDA02V|2024.12.03|19.41|||||ug/dL|-|-||||G|G|0|||||||||VECTC100041";
const char MSG05[] PROGMEM = "$1|SX072|20240318155043|-|teste||Cao|SDMA|SDTDA02V|2024.12.03|Invalid (C.Err)|||||||||||G|G|0||||||teste|||VECTC100041";
const char MSG06[] PROGMEM = "$1|SX072|20240318161711|-|Roni|Ds|Cao|vet D-dimer|DDTBB07V|2024.10.13|Invalid (C.Err)|||||||||||G|G|0||||||cachorro|||VECTC100041";
const char MSG07[] PROGMEM = "$1|SX072|20240320090754|-|Ale|Klaus|Cao|vet D-dimer|DDTBB07V|2024.10.13|6657.96|||||ng/ml|-|-||||G|G|0|||||||||VECTC100041";
const char MSG08[] PROGMEM = "$1|SX072|20240320134539|-|Ale|Klaus|Cao|vet D-dimer|DDTBB07V|2024.10.13|6142.41|||||ng/ml|-|-||||G|G|0||||||123|||VECTC100041";
const char *PRC[] PROGMEM = {MSG01, MSG02, MSG03, MSG04, MSG05, MSG06, MSG07, MSG08};

const char MSG09[] PROGMEM = "MSH|^~\\&|1|ichroma2|TF020||20240215141239||OUL^R24^OUL_R24|1|T|2.6\r\nPID||||||||\r\nOBR||System Check|0||||20240215141239|||-\r\nORC|OK|||||||||||||||||TF020|1\r\nSPM|1|PFRSYTF07|||||||||||||||||20250606\r\nOBX|1|TX|System Check||System OK !|||0|||R";
const char MSG10[] PROGMEM = "MSH|^~\\&|LIS|1021|HIS|1034|200705151727||ORU^R01^ORU_R01|MSG00001|T^T|2.5.1\r\nPID||0001|05689504700|119242517|Ferreira^Felipe^^^^^L^A|Ferreira^Conceição^^^^^L^A|19830610|M|||Estrada da Mombaça^^Saquarema^Rio de Janeiro^28990051^BRA^H\r\nOBR|1|P0001||200705151430|45|2024^Y|20240514153600||45^ml|124/RJ^GestQual Vet|||Sou apenas um campo de observação\r\nOBX||NM|1000764^CREATININE^^^CREA|0001|1.2|mg/dL|.7-1.4||||F|||201005151545||284\r\nOBX||NM|1000765^GLICOSE^^^GLI|0001|91.2|mg/dL|.7-1.4||||F|||201005151545||284\r\nOBX||NM|1000766^COLESTEROL^^^COL|0001|151.2|mg/dL|.7-1.4||||F|||201005151545||284";
const char *HL7[] PROGMEM = {MSG09, MSG10};

const char MSG11[] PROGMEM = "#1|SX022|20240320153613|-|Daniele|Chibally|Cao|vet D-dimer|DDTBB07V|2024.10.13|4955.29|||||ng/ml|-|-||||G|G|0|||||nome de gato|123|||VECTC100041";
const char MSG12[] PROGMEM = "#1|SX022|20240123153959|-||Teste|Cao|vet D-dimer|DDTBB07V|2024.10.13|326.08|||||ng/ml|-|-||||G|G|0|||||||||VECTC100041";
const char *OTHER[] PROGMEM = {MSG11, MSG12};

const char *html PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel='shortcut icon' type='image/svg+xml'
        href="data:image/svg+xml,%3csvg%20xmlns='http://www.w3.org/2000/svg'%20viewBox='.8%20.8%2014.4%2014.4'%3e%3cpath%20d='M10%208.99a1%201%200%2000-.695%201.717l4.004%204a1%201%200%20101.414-1.414l-4.004-4A1%201%200%200010%208.99z'%20fill='%2380b0ff'%20stroke='%235D7FDDaa'%20stroke-width='.3'/%3e%3cpath%20d='M6.508%201C3.48%201%201.002%203.474%201.002%206.5S3.48%2012%206.508%2012s5.504-2.474%205.504-5.5S9.536%201%206.508%201zm0%202a3.486%203.486%200%20013.504%203.5c0%201.944-1.556%203.5-3.504%203.5a3.488%203.488%200%2001-3.506-3.5C3.002%204.556%204.56%203%206.508%203z'%20fill='%2380b0ff'%20stroke='%235D7FDDaa'%20stroke-width='.3'/%3e%3c/svg%3e" />
    <title>ESP32 Web Server</title>
</head>
<body>
    <h1>ESP32 Web Server</h1>
    <form action="/" method="GET">
    <label for="messages">Choose a message:</label>
    <select name="messages">
        <option value="P01">Proccerelator MSG01</option>
        <option value="P02">Proccerelator MSG02</option>
        <option value="P03">Proccerelator MSG03</option>
        <option value="P04">Proccerelator MSG04</option>
        <option value="P05">Proccerelator MSG05</option>
        <option value="P06">Proccerelator MSG06</option>
        <option value="P07">Proccerelator MSG07</option>
        <option value="P08">Proccerelator MSG08</option>
        <option value="PALL">Proccerelator ALL MSGs</option>
        <option value="H01">HL7 MSG01</option>
        <option value="H02">HL7 MSG02</option>
        <option value="HALL">HL7 ALL MSGs</option>
        <option value="O01">OTHER MSG01</option>
        <option value="O02">OTHER MSG02</option>
        <option value="OALL">OTHER ALL MSGs</option>

    </select>
    <input type="submit" value="Send" />
    </form>
</body>
</html>
)rawliteral";