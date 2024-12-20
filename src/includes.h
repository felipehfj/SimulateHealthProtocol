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
const char *VETCHROMA[] PROGMEM = {MSG01, MSG02, MSG03, MSG04, MSG05, MSG06, MSG07, MSG08};

const char MSG09[] PROGMEM =  "MSH|^~\\&|1|ichroma2|TF020||20240215141239||OUL^R24^OUL_R24|1|T|2.6\r\nPID||||||||\r\nOBR||System Check|0||||20240215141239|||-\r\nORC|OK|||||||||||||||||TF020|1\r\nSPM|1|PFRSYTF07|||||||||||||||||20250606\r\nOBX|1|TX|System Check||System OK !|||0|||R";
const char MSG10[] PROGMEM =  "MSH|^~\\&|LIS|1021|HIS|1034|200705151727||ORU^R01^ORU_R01|MSG00001|T^T|2.5.1\r\nPID||0001|05689504700|119242517|Ferreira^Felipe^^^^^L^A|Ferreira^Conceição^^^^^L^A|19830610|M|||Estrada da Mombaça^^Saquarema^Rio de Janeiro^28990051^BRA^H\r\nOBR|1|P0001||200705151430|45|2024^Y|20240514153600||45^ml|124/RJ^GestQual Vet|||Sou apenas um campo de observação\r\nOBX||NM|1000764^CREATININE^^^CREA|0001|1.2|mg/dL|.7-1.4||||F|||201005151545||284\r\nOBX||NM|1000765^GLICOSE^^^GLI|0001|91.2|mg/dL|.7-1.4||||F|||201005151545||284\r\nOBX||NM|1000766^COLESTEROL^^^COL|0001|151.2|mg/dL|.7-1.4||||F|||201005151545||284";
const char MSGVG1[] PROGMEM = "MSH|^~\\&|SMT|VG1|||20241128155729||ORU^R01|2|P|2.3.1|A|||0||ASCII|||1.00.01.22|\r\nPID|2||||^||A|||CÃ£o||||||||1|||||||||||||\r\nOBR|2||3|810000371|||20240830141756||2|3|||1^||Sangue Venoso|||02^9240829^024899240829^Blood Gas Electrolyte15Prazo(BG15)||KAFURI||||||||||||||||||||||||||||\r\nOBX|1|NM|AG*|AG*|21|mmol/L|7-24|N|||F|||||||\r\nOBX|2|NM|BE(b)*|BE(b)*|-0.8|mmol/L|-7.0-6.0|N|||F|||||||\r\nOBX|3|NM|BE(ecf)*|BE(ecf)*|-4.3|mmol/L|-7.0-8.0|N|||F|||||||\r\nOBX|4|NM|cHCO3-*|cHCO3-*|21.1|mmol/L|17.0-32.0|N|||F|||||||\r\nOBX|5|NM|cHgb*|cHgb*|16.4|g/dL|10.0-19.0|N|||F|||||||\r\nOBX|6|NM|cSO2*|cSO2*|65.54|%|55.00-95.00|N|||F|||||||\r\nOBX|7|NM|tCO2*|tCO2*|22.2|mmol/L|18.0-33.0|N|||F|||||||\r\nOBX|8|NM|Hct|Hct|48|%PCV|33-53|N|||F|||||||\r\nOBX|9|NM|pO2|pO2|35|mmHg|30-75|N|||F|||||||\r\nOBX|10|NM|pH|pH|7.363||7.290-7.450|N|||F|||||||\r\nOBX|11|NM|K+|K+|4.00|mmol/L|3.30-5.00|N|||F|||||||\r\nOBX|12|NM|Ca++|Ca++|1.28|mmol/L|1.10-1.35|N|||F|||||||\r\nOBX|13|NM|Na+|Na+|148.6|mmol/L|138.0-150.0|N|||F|||||||\r\nOBX|14|NM|Cl-|Cl-|106.3|mmol/L|106.0-123.0|N|||F|||||||\r\nOBX|15|NM|pCO2|pCO2|37.0|mmHg|34.0-52.0|N|||F|||||||";
const char MMMXX[] PROGMEM =  "MSH|^~\\&|SMT|VG1|||20241128155729||ORU^R01|2|P|2.3.1|A|||0||ASCII|||1.00.01.22|\r\nPID|2||||^||A|||CÃ£o||||||||1|||||||||||||\r\nOBR|2||3|810000371|||20240830141756||2|3|||1^||Sangue Venoso|||02^9240829^024899240829^Blood Gas Electrolyte15Prazo(BG15)||KAFURI||||||||||||||||||||||||||||\r\nOBX|1|NM|AG*|AG*|21|mmol/L|7-24|N|||F|||||||\r\nOBX|2|NM|BE(b)*|BE(b)*|-0.8|mmol/L|-7.0-6.0|N|||F|||||||\r\nOBX|3|NM|BE(ecf)*|BE(ecf)*|-4.3|mmol/L|-7.0-8.0|N|||F|||||||\r\nOBX|4|NM|cHCO3-*|cHCO3-*|21.1|mmol/L|17.0-32.0|N|||F|||||||\r\nOBX|5|NM|cHgb*|cHgb*|16.4|g/dL|10.0-19.0|N|||F|||||||\r\nOBX|6|NM|cSO2*|cSO2*|65.54|%|55.00-95.00|N|||F|||||||\r\nOBX|7|NM|tCO2*|tCO2*|22.2|mmol/L|18.0-33.0|N|||F|||||||\r\nOBX|8|NM|Hct|Hct|48|%PCV|33-53|N|||F|||||||\r\nOBX|9|NM|pO2|pO2|35|mmHg|30-75|N|||F|||||||\r\nOBX|10|NM|pH|pH|7.363||7.290-7.450|N|||F|||||||\r\nOBX|11|NM|K+|K+|4.00|mmol/L|3.30-5.00|N|||F|||||||\r\nOBX|12|NM|Ca++|Ca++|1.28|mmol/L|1.10-1.35|N|||F|||||||\r\nOBX|13|NM|Na+|Na+|148.6|mmol/L|138.0-150.0|N|||F|||||||\r\nOBX|14|NM|Cl-|Cl-|106.3|mmol/L|106.0-123.0|N|||F|||||||\r\nOBX|15|NM|pCO2|pCO2|37.0|mmHg|34.0-52.0|N|||F|||||||\r\n\u001c\r\n\vMSH|^~\\&|SMT|VG1|||20241128155746||ORU^R01|3|P|2.3.1|A|||0||ASCII|||1.00.01.22|\r\nPID|3||||^||A|||Cão||||||||1|||||||||||||\r\nOBR|3||2|810000371|||20240830104008||2|3|||1^||Sangue Venoso|||02^9240829^024899240829^Blood Gas Electrolyte15Prazo(BG15)||KAFURI||||||||||||||||||||||||||||\r\nOBX|1|NM|AG*|AG*|12|mmol/L|7-24|N|||F|||||||\r\nOBX|2|NM|BE(b)*|BE(b)*|-1.7|mmol/L|-7.0-6.0|N|||F|||||||\r\nOBX|3|NM|BE(ecf)*|BE(ecf)*|-5.6|mmol/L|-7.0-8.0|N|||F|||||||\r\nOBX|4|NM|cHCO3-*|cHCO3-*|20.9|mmol/L|17.0-32.0|N|||F|||||||\r\nOBX|5|NM|cHgb*|cHgb*|10.4|g/dL|10.0-19.0|N|||F|||||||\r\nOBX|6|NM|cSO2*|cSO2*|68.64|%|55.00-95.00|N|||F|||||||\r\nOBX|7|NM|tCO2*|tCO2*|22.2|mmol/L|18.0-33.0|N|||F|||||||\r\nOBX|8|NM|Hct|Hct|31|%PCV|33-53|L|||F|||||||\r\nOBX|9|NM|pO2|pO2|40|mmHg|30-75|N|||F|||||||\r\nOBX|10|NM|pH|pH|7.292||7.290-7.450|N|||F|||||||\r\nOBX|11|NM|K+|K+|4.73|mmol/L|3.30-5.00|N|||F|||||||\r\nOBX|12|NM|Ca++|Ca++|1.36|mmol/L|1.10-1.35|H|||F|||||||\r\nOBX|13|NM|Na+|Na+|143.6|mmol/L|138.0-150.0|N|||F|||||||\r\nOBX|14|NM|Cl-|Cl-|110.8|mmol/L|106.0-123.0|N|||F|||||||\r\nOBX|15|NM|pCO2|pCO2|43.3|mmHg|34.0-52.0|N|||F|||||||\r\n\u001c\r\n\vMSH|^~\\&|SMT|VG1|||20241128155802||ORU^R01|4|P|2.3.1|A|||0||ASCII|||1.00.01.22|\r\nPID|4||||^||A|||CÃ£o||||||||1|||||||||||||\r\nOBR|4||1|810000371|||20240830101957||2|3|||1^||Sangue Venoso|||02^9240829^024899240829^Blood Gas Electrolyte15Prazo(BG15)||KAFURI||||||||||||||||||||||||||||\r\nOBX|1|NM|AG*|AG*|13|mmol/L|7-24|N|||F|||||||\r\nOBX|2|NM|BE(b)*|BE(b)*|-0.2|mmol/L|-7.0-6.0|N|||F|||||||\r\nOBX|3|NM|BE(ecf)*|BE(ecf)*|0.2|mmol/L|-7.0-8.0|N|||F|||||||\r\nOBX|4|NM|cHCO3-*|cHCO3-*|25.2|mmol/L|17.0-32.0|N|||F|||||||\r\nOBX|5|NM|cHgb*|cHgb*|15.3|g/dL|10.0-19.0|N|||F|||||||\r\nOBX|6|NM|cSO2*|cSO2*|45.12|%|55.00-95.00|L|||F|||||||\r\nOBX|7|NM|tCO2*|tCO2*|26.4|mmol/L|18.0-33.0|N|||F|||||||\r\nOBX|8|NM|Hct|Hct|45|%PCV|33-53|N|||F|||||||\r\nOBX|9|NM|pO2|pO2|25|mmHg|30-75|L|||F|||||||\r\nOBX|10|NM|pH|pH|7.390||7.290-7.450|N|||F|||||||\r\nOBX|11|NM|K+|K+|4.11|mmol/L|3.30-5.00|N|||F|||||||\r\nOBX|12|NM|Ca++|Ca++|1.24|mmol/L|1.10-1.35|N|||F|||||||\r\nOBX|13|NM|Na+|Na+|149.1|mmol/L|138.0-150.0|N|||F|||||||\r\nOBX|14|NM|Cl-|Cl-|111.2|mmol/L|106.0-123.0|N|||F|||||||\r\nOBX|15|NM|pCO2|pCO2|41.6|mmHg|34.0-52.0|N|||F|||||||\r\n\u001c\r\n\vMSH|^~\\&|SMT|VG1|||20241128155818||ORU^R01|5|P|2.3.1|A|||0||ASCII|||1.00.01.22|\r\nPID|5||||^||A|||CÃ£o||||||||1|||||||||||||\r\nOBR|5||8|810000371|||20240829171239||2|3|||1^||Sangue Venoso|||02^9240829^024899240829^Blood Gas Electrolyte15Prazo(BG15)||KAFURI||||||||||||||||||||||||||||\r\nOBX|1|NM|AG*|AG*|9|mmol/L|7-24|N|||F|||||||\r\nOBX|2|NM|BE(b)*|BE(b)*|-0.8|mmol/L|-7.0-6.0|N|||F|||||||\r\nOBX|3|NM|BE(ecf)*|BE(ecf)*|-3.8|mmol/L|-7.0-8.0|N|||F|||||||\r\nOBX|4|NM|cHCO3-*|cHCO3-*|21.7|mmol/L|17.0-32.0|N|||F|||||||\r\nOBX|5|NM|cHgb*|cHgb*|15.1|g/dL|10.0-19.0|N|||F|||||||\r\nOBX|6|NM|cSO2*|cSO2*|73.20|%|55.00-95.00|N|||F|||||||\r\nOBX|7|NM|tCO2*|tCO2*|22.8|mmol/L|18.0-33.0|N|||F|||||||\r\nOBX|8|NM|Hct|Hct|44|%PCV|33-53|N|||F|||||||\r\nOBX|9|NM|pO2|pO2|40|mmHg|30-75|N|||F|||||||\r\nOBX|10|NM|pH|pH|7.359||7.290-7.450|N|||F|||||||\r\nOBX|11|NM|K+|K+|4.14|mmol/L|3.30-5.00|N|||F|||||||\r\nOBX|12|NM|Ca++|Ca++|1.25|mmol/L|1.10-1.35|N|||F|||||||\r\nOBX|13|NM|Na+|Na+|141.2|mmol/L|138.0-150.0|N|||F|||||||\r\nOBX|14|NM|Cl-|Cl-|110.8|mmol/L|106.0-123.0|N|||F|||||||\r\nOBX|15|NM|pCO2|pCO2|38.4|mmHg|34.0-52.0|N|||F|||||||\r\n\u001c\r\n\vMSH|^~\\&|SMT|VG1|||20241128155835||ORU^R01|6|P|2.3.1|A|||0||ASCII|||1.00.01.22|\r\nPID|6||||^||A|||CÃ£o||||||||1|||||||||||||\r\nOBR|6||7|810000371|||20240829165641||2|3|||1^||Sangue Venoso|||02^9240829^024899240829^Blood Gas Electrolyte15Prazo(BG15)||KAFURI||||||||||||||||||||||||||||\r\nOBX|1|NM|AG*|AG*|19|mmol/L|7-24|N|||F|||||||\r\nOBX|2|NM|BE(b)*|BE(b)*|0.2|mmol/L|-7.0-6.0|N|||F|||||||\r\nOBX|3|NM|BE(ecf)*|BE(ecf)*|-1.0|mmol/L|-7.0-8.0|N|||F|||||||\r\nOBX|4|NM|cHCO3-*|cHCO3-*|23.6|mmol/L|17.0-32.0|N|||F|||||||\r\nOBX|5|NM|cHgb*|cHgb*|17.6|g/dL|10.0-19.0|N|||F|||||||\r\nOBX|6|NM|cSO2*|cSO2*|71.99|%|55.00-95.00|N|||F|||||||\r\nOBX|7|NM|tCO2*|tCO2*|24.8|mmol/L|18.0-33.0|N|||F|||||||\r\nOBX|8|NM|Hct|Hct|52|%PCV|33-53|N|||F|||||||\r\nOBX|9|NM|pO2|pO2|37|mmHg|30-75|N|||F|||||||\r\nOBX|10|NM|pH|pH|7.407||7.290-7.450|N|||F|||||||\r\nOBX|11|NM|K+|K+|4.29|mmol/L|3.30-5.00|N|||F|||||||\r\nOBX|12|NM|Ca++|Ca++|1.26|mmol/L|1.10-1.35|N|||F|||||||\r\nOBX|13|NM|Na+|Na+|149.9|mmol/L|138.0-150.0|N|||F|||||||\r\nOBX|14|NM|Cl-|Cl-|106.8|mmol/L|106.0-123.0|N|||F|||||||\r\nOBX|15|NM|pCO2|pCO2|37.6|mmHg|34.0-52.0|N|||F|||||||";
const char *HL7[] PROGMEM = {MSG09, MSG10};

const char MSG11[] PROGMEM = "#1|SX022|20240320153613|-|Daniele|Chibally|Cao|vet D-dimer|DDTBB07V|2024.10.13|4955.29|||||ng/ml|-|-||||G|G|0|||||nome de gato|123|||VECTC100041";
const char MSG12[] PROGMEM = "#1|SX022|20240123153959|-||Teste|Cao|vet D-dimer|DDTBB07V|2024.10.13|326.08|||||ng/ml|-|-||||G|G|0|||||||||VECTC100041";
const char *OTHER[] PROGMEM = {MSG11, MSG12};

const char MSG13[] PROGMEM = "*T0016ANIMAL4T2       00112023082511050504VET 11AC  B2345678CD9A1011043300101D902ED02E703AD032702A3037502E702A9010D0188014B0386032101C4015601E20144028302AF0193029D0333026702D701D5010203ED03C2036F03AF035002F8";
const char MSG14[] PROGMEM = "*T0030URITROL1LIO     00002023091510494904VET 11AC  B2345678CD9A0005000000001F2032D039303C30380032B039D03590346029E021F014303BB031B01C903D701C70140039B030101B80399037E02F4033101BF00F203E403CC03DC03B4038F039A";
const char *URIDOCTORALL[] PROGMEM = {MSG13, MSG14};

const char MSG15[] PROGMEM = "��aa, 00001,                     , 2024.08.07, 11:26, 57, 5, 7.441,  35.9,  42.1,  4.07, 130.3,  1.33,  41.1,  25.2,  24.1,   0.3,  80.0,  14.0,  24.5,  -0.1,  47.9,  15.7,  62.7, * , 7.441,  35.9,  42.1,  2.86, H,  , L,  , L,  ,  , -,  37.0,  0.21, 760.0, bb";
const char MSG16[] PROGMEM = "�aa, 00002,                     , 2024.08.07, 15:05, 57, 5, 7.439,  41.2,  33.5,  4.93, 142.0,  1.38,  40.8,  28.8,  27.5,   3.1,  67.0,  13.9,  26.5,   3.4,  50.6,  13.0,  64.8, * , 7.439,  41.2,  33.5,  2.94, H,  , L,  ,  ,  ,  , -,  37.0,  0.21, 760.0, bb";
const char MSG17[] PROGMEM = "�aa, 00022,                     , 2024.08.29, 16:07, 57, 5, 7.392,  53.9,  30.3,  3.95, 135.2,  1.28,  33.0,  33.8,  32.1,   6.0,  56.1,  11.2,  29.0,   7.2,  52.4,   8.9,  52.1, * , 7.392,  53.9,  30.3,  2.68,  , H, L,  , L,  , L, -,  37.0,  0.21, 760.0, bb";
const char * ICHECKRALL[] PROGMEM = {MSG15, MSG16, MSG17};

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
        <option value="P01">VetChroma MSG01</option>        
        <option value="P02">VetChroma MSG02</option>
        <option value="P03">VetChroma MSG03</option>
        <option value="P04">VetChroma MSG04</option>
        <option value="P05">VetChroma MSG05</option>
        <option value="P06">VetChroma MSG06</option>
        <option value="P07">VetChroma MSG07</option>
        <option value="P08">VetChroma MSG08</option>
        <option value="PALL">VetChroma ALL MSGs</option>
        <option value="U01">Uridoctor MSG01</option>
        <option value="U02">Uridoctor MSG02</option>
        <option value="UALL">Uridoctor ALL MSGs</option>
        <option value="I01">ICheck MSG01</option>
        <option value="I02">ICheck MSG02</option>
        <option value="I03">ICheck MSG03</option>
        <option value="IALL">ICheck ALL MSGs</option>
        <option value="H01">HL7 MSG01</option>
        <option value="H02">HL7 MSG02</option>
        <option value="H03">HL7 MSG03</option>
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

//"\vMSH|^~\\&|1|ichroma2|TF020||20240215141239||OUL^R24^OUL_R24|1|T|2.6\r\nPID||||||||\r\nOBR||System Check|0||||20240215141239|||-\r\nORC|OK|||||||||||||||||TF020|1\r\nSPM|1|PFRSYTF07|||||||||||||||||20250606\r\nOBX|1|TX|System Check||System OK !|||0|||R0x1c\n\r"