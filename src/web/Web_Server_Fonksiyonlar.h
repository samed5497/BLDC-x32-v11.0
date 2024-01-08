#include <Degisken_Fonksiyonlar.h>

void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        Serial.println("WebSoket Bağlantısı Kuruldu");
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        Serial.println("WebSoket Bağlantısı Kapatıldı");
    }
    else if (type == WS_EVT_DATA)
    {
        AwsFrameInfo *info = (AwsFrameInfo *)arg;
        if (info->opcode == WS_TEXT)
        {
            data[len] = '\0';
            String receivedMessage = String((char *)data);
            if (receivedMessage == "systempowerOn")
            {
                system_power = true;
            }
            else if (receivedMessage == "systempowerOff")
            {
                system_power = false;
            }
        }
    }

    if (system_power)
    {
        server->textAll("systempowerOn");
    }
    else
    {
        server->textAll("systempowerOff");
    }
}

String generateSettingsForm()
{

    String SettingsPageScript = String("<style>") +
                                "body { font-family: Arial, sans-serif; background-color: #f4f4f4; }" +
                                "h1 { color: #333; text-align: center; }" +
                                "form { margin: 0 auto; max-width: 400px; padding: 20px; background: #fff; border-radius: 5px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); position: relative; }" +
                                "label { display: block; margin-bottom: 5px; }" +
                                "input[type='password'], input[type='text'], select { width: calc(100% - 12px); padding: 5px; margin-bottom: 10px; border: 1px solid #ccc; border-radius: 3px; }" +
                                ".toggle-password { position: absolute; top: 50%; right: 5px; transform: translateY(-50%); width: 20px; height: 20px; background: #ccc; border: none; cursor: pointer; padding: 0; }" +
                                "input[type='submit'] { background-color: #4caf50; color: white; padding: 10px 20px; border: none; border-radius: 3px; cursor: pointer; display: block; margin: 0 auto; }" +
                                "</style>";

    String SettingsPagecss = String("<script>") +
                             "function togglePassword() {var passField = document.getElementById('pass_STA');" +
                             "  if (passField.type === 'password') {passField.type = 'text';}" +
                             "  else {passField.type = 'password';}}" +
                             "</script>";

    String SettingsPagehtml = String("<!DOCTYPE html><html><head><meta charset='UTF-8'><title>" + UYGULAMA + " Wi-Fi Yapılandırma</title></head><body>") +
                              SettingsPagecss +
                              SettingsPageScript + "<h1>Wi-Fi Yapılandırma</h1>" +
                              "<form method='post' action='setap'>" +
                              "<label for='ssid_STA'>SSID:</label><select name='ssid_STA'>" + ssidList + "</select><br><br>" +
                              "<label for='pass_STA'>Şifre:</label><div style='position: relative;'>" +
                              "<input name='pass_STA' id='pass_STA' maxlength =64 type='password'>" +
                              "<input type='button' class='toggle-password' onclick='togglePassword()' value='👁️'></div>" +
                              "<br><br>" +
                              "<label for='APP_KEY'>APP Key:</label><input name='APP_KEY' maxlength =64 type='text'><br><br>" +
                              "<label for='APP_SECRET'>APP Secret:</label><input name='APP_SECRET' maxlength =128 type='text'><br><br>" +
                              "<label for='DEVICE_ID'>Device ID:</label><input name='DEVICE_ID' maxlength =64 type='text'><br><br>" +
                              "<input type='submit' value='Gönder'></form>" +
                              "</body></html>";

    return SettingsPagehtml;
}

String generateFirstPageForm()
{

    String FirstPageScript = String("<script> </script>");

    String FirstPagecss = String("<style>") +
                          "body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }" +
                          "h1 { color: #333; } p { color: #555; }" +
                          ".settings-btn { background-color: #4caf50; color: white; padding: 10px 20px; text-decoration: none; border-radius: 5px; }" +
                          ".content { max-width: 400px; margin: 0 auto; background-color: #fff; padding: 20px; border-radius: 5px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); }" +
                          "</style>";

    String FirstPagehtml = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>" + UYGULAMA + " Wi-Fi Yapılandırma</ title></ head> < body > " +
                           FirstPagecss +
                           FirstPageScript +
                           "<div class='content'>" +
                           "<h1" + UYGULAMA + "</h1>" +
                           "<p>Cihazınız için özel Wi-Fi ağınızın ayarlarını yapılandırmak için aşağıdaki butona tıklayın.</p><br>" +
                           "<p><a href=\"/settings\" class='settings-btn'>Yapılandırma</a></p></div>" +
                           "</body></html>";

    return FirstPagehtml;
}

String generateResetForm()
{
    String ResetPageScript = String("<script> </script>");

    String ResetPagecss = String("<style>") +
                          "body { font-family: Arial, sans-serif; background-color: #f4f4f4; text-align: center; }" +
                          "h1 { color: #333; } p { color: #555; }" +
                          ".content { max-width: 400px; margin: 0 auto; background: #fff; border-radius: 5px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); padding: 20px; }" +
                          "label { display: block; margin-bottom: 5px; }" +
                          "input[type='text'] { width: calc(100% - 12px); padding: 5px; margin-bottom: 10px; border: 1px solid #ccc; border-radius: 3px; }" +
                          ".submit-button { background-color: #4caf50; color: white; padding: 10px 20px; border: none; border-radius: 3px; cursor: pointer; }" +
                          ".button { padding: 10px 20px; font-size: 18px; background-color: #007bff; color: #fff; border: none; border-radius: 5px; cursor: pointer; text-decoration: none; }" +
                          "</style>";

    String ResetPagehtml = String("<!DOCTYPE html<html><head><meta charset='UTF-8'><title>" + UYGULAMA + " Fabrika Ayarları</title></head><body>") +
                           ResetPageScript +
                           ResetPagehtml +
                           "<div class='content'>" + "<h1>Wi-Fi ayarları sıfırlandı!</h1>" +
                           "<p>Değişiklikler cihazı yeniden başlattığınızda devreye alınacaktır. Yeniden başlatana kadar mevcut sistem çalışmaya devam edecektir. </p>" +
                           "<p>Cihaz yeniden başlatıldığında <strong><em>" + ssid_AP + "</strong></em> ismiyle Wifi paylaşımına başlayacaktır. </p><br></div>" +
                           "<a href='/' class='button'>Ana Sayfaya Dön</a>" + // Buton ile ana sayfaya yönlendirme

                           "</body></html>";

    return ResetPagehtml;
}

String generateSettingsFinishForm()
{
    String SettingsPageScript = String("<style>") +
                                "body { font-family: Arial, sans-serif; background-color: #f4f4f4; }" +
                                "h1 { color: #333; text-align: center; }" +
                                "form { margin: 0 auto; max-width: 400px; padding: 20px; background: #fff; border-radius: 5px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); position: relative; }" +
                                "label { display: block; margin-bottom: 5px; }" +
                                "input[type='password'], input[type='text'], select { width: calc(100% - 12px); padding: 5px; margin-bottom: 10px; border: 1px solid #ccc; border-radius: 3px; }" +
                                ".toggle-password { position: absolute; top: 50%; right: 5px; transform: translateY(-50%); width: 20px; height: 20px; background: #ccc; border: none; cursor: pointer; padding: 0; }" +
                                "input[type='submit'] { background-color: #4caf50; color: white; padding: 10px 20px; border: none; border-radius: 3px; cursor: pointer; display: block; margin: 0 auto; }" +
                                "</style>";

    String SettingsPagecss = String("<script>") +
                             "function togglePassword() {var passField = document.getElementById('pass_STA');" +
                             "  if (passField.type === 'password') {passField.type = 'text';}" +
                             "  else {passField.type = 'password';}}" +
                             "</script>";

    String SettingsPagehtml = String("<!DOCTYPE html><html><head><meta charset='UTF-8'><title>" + UYGULAMA + " Wi-Fi Yapılandırma</title></head><body>") +
                              SettingsPagecss +
                              SettingsPageScript + "<h1>Wi-Fi Yapılandırma</h1>" +
                              "<form method='post' action='setap'>" +
                              "<label for='ssid_STA'>SSID:</label><select name='ssid_STA'>" + ssidList + "</select><br><br>" +
                              "<label for='pass_STA'>Şifre:</label><div style='position: relative;'>" +
                              "<input name='pass_STA' id='pass_STA' maxlength =64 type='password'>" +
                              "<input type='button' class='toggle-password' onclick='togglePassword()' value='👁️'></div>" +
                              "<br><br>" +
                              "<label for='APP_KEY'>APP Key:</label><input name='APP_KEY' maxlength =64 type='text'><br><br>" +
                              "<label for='APP_SECRET'>APP Secret:</label><input name='APP_SECRET' maxlength =128 type='text'><br><br>" +
                              "<label for='DEVICE_ID'>Device ID:</label><input name='DEVICE_ID' maxlength =64 type='text'><br><br>" +
                              "<input type='submit' value='Gönder'></form>" +
                              "</body></html>";

    return SettingsPagehtml;
}

String generateMainPageForm()
{

    String MainPageScript = String("<script>var ws=new WebSocket('ws://' + window.location.hostname + ':80/ws');") +

                            // WebSocket ile server'dan güncelleme alındığında çalışacak fonksiyon
                            "ws.onmessage = function (event) {var data = event.data;" +
                            "   if      (data === 'systempowerOn') {document.getElementById('system_powerSwitch').checked = true}" +
                            "   else if (data === 'systempowerOff') {document.getElementById('system_powerSwitch').checked = false;}};" +

                            "ws.onerror = function(event) {" +
                            "alert('Bağlantı hatası! Sayfa yeniden yüklenecek.'); window.location.reload();};" +

                            "function sendRequest(url) {" +
                            "   fetch(url).then(response => {" +
                            "   if (response.ok) {console.log('İstek başarıyla gönderildi!');}" +
                            "   else {console.error('İstekte bir hata oluştu.');}}).catch(error => {console.error('Bir hata oluştu:', error);});}" +


                            "function confirmReset() {" +
                            "   return confirm('Fabrika ayarlarına dönmek istediğinize emin misiniz? Onay vermeniz durumunda hafızada kayıtlı olan tüm bilgiler silinecek ve cihazı tekrar kullanabilmek için yeniden internet yapılandırması yapmanız gerekecektir.');}" +

                            "function resetDevice() {" +
                            "   if (confirmReset()) {sendRequest('/reset');window.location.href = '/reset';}}" +

                            "function confirmRestart() {" +
                            "   return confirm('Sistem Yeniden Başlatılacaktır. Onaylıyor musunuz?');}" +

                            "function restartDevice() {" +
                            "   if (confirmRestart()) {sendRequest('/restart');var countDown = 1;var countdownInterval = setInterval(function() {" +
                            "   if (countDown > 0) {alert('Sistem yeniden başlatılıyor. Sayfa otomatik olarak yeniden yüklenecektir.');countDown--;} " +
                            "   else {clearInterval(countdownInterval);" +
                            "   alert('Sistem yeniden başlatıldı.'); window.location.reload();}}, 2500);}}" +

                            "function clearInputFields() {" +
                            "   document.getElementById('username').value = ''; document.getElementById('password').value = '';}" +

                            "function authenticateUser() {" +
                            "   var username = document.getElementById('username').value; var password = document.getElementById('password').value;" +
                            "   if (username === 'admin' && password === 'admin') {clearInputFields();document.getElementById('loginPopup').style.display = 'none';document.getElementById('advancedSettingsPopup').style.display = 'block';}" +
                            "   else {clearInputFields();alert('Kullanıcı adı veya şifre yanlış!');}}" +

                            // system_power durumunun değişmesini takip eden fonksiyon
                            "function changesystem_power() {var system_powerSwitch = document.getElementById('system_powerSwitch'); var isChecked = system_powerSwitch.checked;" +
                            "if (isChecked) {ws.send('systempowerOn');} " +
                            "else { ws.send('systempowerOff');}}" +

                            "function closeAdvancedSettingsPopup() {" +
                            "   document.getElementById('advancedSettingsPopup').style.display = 'none';}" +

                            "function updateCPUTemperature() {" +
                            "   fetch('/getCPUTemperature').then(response => response.text()).then(data => {document.getElementById('cpuTemp').innerText = data + ' °C';}).catch(error => {console.error('Hata:', error);});}" +
                            "   setInterval(updateCPUTemperature, 500);" +

                            "function updateDuty() {" +
                            "   fetch('/getDuty').then(response => response.text()).then(data => {document.getElementById('dutydeger').innerText = '% ' + data;}).catch(error => {console.error('Hata:', error);});}" +
                            "   setInterval(updateDuty, 500);" +

                            "function updateBekleme() {" +
                            "   fetch('/getbekleme').then(response => response.text()).then(data => {document.getElementById('beklemedeger').innerText = data + ' us';}).catch(error => {console.error('Hata:', error);});}" +
                            "   setInterval(updateBekleme, 500);" +

                            "function updateCurrent() {" +
                            "   fetch('/getCurrent').then(response => response.text()).then(data => {document.getElementById('syscurrent').innerText = data + ' Mah';}).catch(error => {console.error('Hata:', error);});}" +
                            "   setInterval(updateCurrent, 500);" +

                            "function updateTemp() {" +
                            "   fetch('/getTemp').then(response => response.text()).then(data => {document.getElementById('systemp').innerText = data + ' °C';}).catch(error => {console.error('Hata:', error);});}" +
                            "   setInterval(updateTemp, 500);" +

                            "function updateTemp_A() {" +
                            "   fetch('/getTemp_A').then(response => response.text()).then(data => {document.getElementById('systemp_A').innerText = data + ' °C';}).catch(error => {console.error('Hata:', error);});}" +
                            "   setInterval(updateTemp_A, 500);" +

                            "function updateTemp_B() {" +
                            "   fetch('/getTemp_B').then(response => response.text()).then(data => {document.getElementById('systemp_B').innerText = data + ' °C';}).catch(error => {console.error('Hata:', error);});}" +
                            "   setInterval(updateTemp_B, 500);" +

                            "function updateTemp_C() {" +
                            "   fetch('/getTemp_C').then(response => response.text()).then(data => {document.getElementById('systemp_C').innerText = data + ' °C';}).catch(error => {console.error('Hata:', error);});}" +
                            "   setInterval(updateTemp_C, 500);" +

                            "function updateFreq() {" +
                            "   fetch('/getFreq').then(response => response.text()).then(data => {document.getElementById('sysfrekans').innerText = data + ' Hz';}).catch(error => {console.error('Hata:', error);});}" +
                            "   setInterval(updateFreq, 500);" +

                            "function DUTYarttir() {" +
                            "   sendRequest('/duytarttir');}" +

                            "function DUTYazalt() {" +
                            "   sendRequest('/duytazalt');}" +

                            "function BEKLEMEarttir() {" +
                            "   sendRequest('/beklemearttir');}" +

                            "function BEKLEMEazalt() {" +
                            "   sendRequest('/beklemeazalt');}" +

                            "function updateWorkingTime() {" +
                            "   fetch('/updateWorkingTime').then(response => response.text()).then(data => {document.getElementById('sysWorkingTime').innerText = data;}).catch(error => {console.error('Hata:', error);});}" +
                            "   setInterval(updateWorkingTime, 500);" +

                            "</script>";

    String MainPagecss = String("<style>") +
                         "@import url('https://fonts.googleapis.com/css2?family=Roboto:wght@400;500&display=swap');" +
                         "html {height: 100%;}" +
                         "body { font-family: Arial, sans-serif; background-color: #f4f4f4; text-align: center; }" +
                         "h1 { color: #333; }" + ".controlButton {border-radius: 10px; border: none; background: blue; width: 100px; height: 100px; display: flex; align-items: center; justify-content: center; cursor: pointer; outline: none; transition: .3s ease-in-out;}" +
                         ".controlButton:hover {transition: .3s ease-in-out; opacity: 0.8;}" +
                         ".startButton {background: #24ec70;}" +
                         ".stopButton {background: #ec243b;}" +
                         ".controlButton svg {width: 60px; fill: white;}" +
                         ".controlButton path {fill: white;}" +
                         ".buttonsDiv {text-align: center;display: flex; gap: 15px;}" +
                         ".buttonsDiv > div button:nth-of-type(1) {margin-bottom: 15px;}" +
                         ".buttonsDivTitle {text-align: center; font-size: 14px; font-weight: 500; margin-bottom: 5px;}" +
                         ".buttonsDivTitle2 {text-align: center; font-size: 15px; font-weight: 500; margin-top: 5px;}" +
                         ".dataBox {height: calc(200px / 3); max-height: 100px; width: 200px; border-radius: 10px; border: none; background: #e1e1e1; display: flex; align-items: center; justify-content: space-between; padding: 0 15px;}" +
                         ".dataBox:first-child {margin-top: 22px;}" +
                         ".dataBox:nth-of-type(2) {margin: 7.5px 0;}" +
                         ".dataBoxTitle {font-size: 15px; font-weight: 500; color: black;}" +
                         ".dataBoxValue {font-size: 18px; font-weight: 500; color: black;}" +
                         ".form-container {  display: flex; flex-direction: column; align-items: center;  max-width: 800px; margin: 0 auto; padding: 20px; background: rgba(255, 255, 255, 0.8); border-radius: 5px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.3); }" +
                         ".popup { display: none; position: fixed; left: 50%; top: 50%; transform: translate(-50%, -50%); z-index: 9999; background-color: rgba(255, 255, 255, 0.9); border: 1px solid #ccc; border-radius: 5px; padding: 20px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.3); }" +
                         ".popup form label { display: inline-block; width: 80px; }" +                                         // Ayarlarınızı yapabilirsiniz
                         ".popup form input[type='text'], .popup form input[type='password'] { width: calc(100% - 100px); }" + // inputların boyutu
                         ".close { position: absolute; top: 10px; right: 10px; cursor: pointer; font-size: 24px; }" +

                         ".switch {position: relative; display: inline-block; width: 60px; height: 34px;}" +
                         ".switch input {display: none;}" +
                         ".slider {position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; transition: .4s; border-radius: 34px;}" +
                         ".slider:before {position: absolute; content: ''; height: 26px; width: 26px; left: 4px; bottom: 4px; background-color: white; transition: .4s; border-radius: 50%;}" +
                         "input:checked + .slider {background-color: #2196F3;}" +
                         "input:checked + .slider:before {transform: translateX(26px);}" +
                         ".slider.round {border-radius: 34px;}" +
                         ".slider.round:before {border-radius: 50%;}" +

                         "</style>";

    String MainPagehtlm = String("<!DOCTYPE html><html><head><meta charset = 'UTF-8'><title>" + UYGULAMA + " Anasayfa</title></head><body>") +
                          MainPagecss +
                          MainPageScript +

                          "<div class='form-container'>"
                          "<h2>Kontrol</h2>" +

                          "<div class='buttonsDiv'><div>" +
                          "<div class='buttonsDivTitle'><strong>Sistem Enerji</strong></div>" +

                          "<label class='switch'>" +
                          "<input type='checkbox' id='system_powerSwitch' onchange='changesystem_power()' " + (system_power ? "checked" : "") + ">" +
                          "<span class='slider round'></span></label>" +
                          "</div>" +

                          "<div>" +
                          "<div class='buttonsDivTitle'><strong>DUTY</strong></div>" +
                          "<button class='controlButton' type='button' onclick='DUTYarttir()'><svg viewBox='0 0 24 24' fill='none' xmlns='http://www.w3.org/2000/svg'><path d='M6.4569 9.73276C6.17123 10.0327 6.18281 10.5074 6.48276 10.7931C6.78271 11.0788 7.25744 11.0672 7.5431 10.7672L6.4569 9.73276ZM12.5431 5.51724C12.8288 5.21729 12.8172 4.74256 12.5172 4.4569C12.2173 4.17123 11.7426 4.18281 11.4569 4.48276L12.5431 5.51724ZM12.5431 4.48276C12.2574 4.18281 11.7827 4.17123 11.4828 4.4569C11.1828 4.74256 11.1712 5.21729 11.4569 5.51724L12.5431 4.48276ZM16.4569 10.7672C16.7426 11.0672 17.2173 11.0788 17.5172 10.7931C17.8172 10.5074 17.8288 10.0327 17.5431 9.73276L16.4569 10.7672ZM12.75 5C12.75 4.58579 12.4142 4.25 12 4.25C11.5858 4.25 11.25 4.58579 11.25 5H12.75ZM11.25 19C11.25 19.4142 11.5858 19.75 12 19.75C12.4142 19.75 12.75 19.4142 12.75 19H11.25ZM7.5431 10.7672L12.5431 5.51724L11.4569 4.48276L6.4569 9.73276L7.5431 10.7672ZM11.4569 5.51724L16.4569 10.7672L17.5431 9.73276L12.5431 4.48276L11.4569 5.51724ZM11.25 5V19H12.75V5H11.25Z' fill='#000000'/></svg></button>" +
                          "<button class='controlButton' type='button' onclick='DUTYazalt()'><svg viewBox='0 0 24 24' fill='none' xmlns='http://www.w3.org/2000/svg' transform='rotate(180)'><path d='M6.4569 9.73276C6.17123 10.0327 6.18281 10.5074 6.48276 10.7931C6.78271 11.0788 7.25744 11.0672 7.5431 10.7672L6.4569 9.73276ZM12.5431 5.51724C12.8288 5.21729 12.8172 4.74256 12.5172 4.4569C12.2173 4.17123 11.7426 4.18281 11.4569 4.48276L12.5431 5.51724ZM12.5431 4.48276C12.2574 4.18281 11.7827 4.17123 11.4828 4.4569C11.1828 4.74256 11.1712 5.21729 11.4569 5.51724L12.5431 4.48276ZM16.4569 10.7672C16.7426 11.0672 17.2173 11.0788 17.5172 10.7931C17.8172 10.5074 17.8288 10.0327 17.5431 9.73276L16.4569 10.7672ZM12.75 5C12.75 4.58579 12.4142 4.25 12 4.25C11.5858 4.25 11.25 4.58579 11.25 5H12.75ZM11.25 19C11.25 19.4142 11.5858 19.75 12 19.75C12.4142 19.75 12.75 19.4142 12.75 19H11.25ZM7.5431 10.7672L12.5431 5.51724L11.4569 4.48276L6.4569 9.73276L7.5431 10.7672ZM11.4569 5.51724L16.4569 10.7672L17.5431 9.73276L12.5431 4.48276L11.4569 5.51724ZM11.25 5V19H12.75V5H11.25Z' fill='#000000'></path> </svg> </button>" +
                          "<div class='buttonsDivTitle2'> <span id='dutydeger'></span> </div>" +
                          "</div>" +

                          "<div>" +
                          "<div class='buttonsDivTitle'><strong>BEKLEME</strong></div>" +
                          "<button class='controlButton' type='button' onclick='BEKLEMEarttir()' ><svg viewBox='0 0 24 24' fill='none' xmlns='http://www.w3.org/2000/svg'><path d='M6.4569 9.73276C6.17123 10.0327 6.18281 10.5074 6.48276 10.7931C6.78271 11.0788 7.25744 11.0672 7.5431 10.7672L6.4569 9.73276ZM12.5431 5.51724C12.8288 5.21729 12.8172 4.74256 12.5172 4.4569C12.2173 4.17123 11.7426 4.18281 11.4569 4.48276L12.5431 5.51724ZM12.5431 4.48276C12.2574 4.18281 11.7827 4.17123 11.4828 4.4569C11.1828 4.74256 11.1712 5.21729 11.4569 5.51724L12.5431 4.48276ZM16.4569 10.7672C16.7426 11.0672 17.2173 11.0788 17.5172 10.7931C17.8172 10.5074 17.8288 10.0327 17.5431 9.73276L16.4569 10.7672ZM12.75 5C12.75 4.58579 12.4142 4.25 12 4.25C11.5858 4.25 11.25 4.58579 11.25 5H12.75ZM11.25 19C11.25 19.4142 11.5858 19.75 12 19.75C12.4142 19.75 12.75 19.4142 12.75 19H11.25ZM7.5431 10.7672L12.5431 5.51724L11.4569 4.48276L6.4569 9.73276L7.5431 10.7672ZM11.4569 5.51724L16.4569 10.7672L17.5431 9.73276L12.5431 4.48276L11.4569 5.51724ZM11.25 5V19H12.75V5H11.25Z' fill='#000000'/></svg> </button>" +
                          "<button class='controlButton' type='button' onclick='BEKLEMEazalt()' ><svg viewBox='0 0 24 24' fill='none' xmlns='http://www.w3.org/2000/svg' transform='rotate(180)'><path d='M6.4569 9.73276C6.17123 10.0327 6.18281 10.5074 6.48276 10.7931C6.78271 11.0788 7.25744 11.0672 7.5431 10.7672L6.4569 9.73276ZM12.5431 5.51724C12.8288 5.21729 12.8172 4.74256 12.5172 4.4569C12.2173 4.17123 11.7426 4.18281 11.4569 4.48276L12.5431 5.51724ZM12.5431 4.48276C12.2574 4.18281 11.7827 4.17123 11.4828 4.4569C11.1828 4.74256 11.1712 5.21729 11.4569 5.51724L12.5431 4.48276ZM16.4569 10.7672C16.7426 11.0672 17.2173 11.0788 17.5172 10.7931C17.8172 10.5074 17.8288 10.0327 17.5431 9.73276L16.4569 10.7672ZM12.75 5C12.75 4.58579 12.4142 4.25 12 4.25C11.5858 4.25 11.25 4.58579 11.25 5H12.75ZM11.25 19C11.25 19.4142 11.5858 19.75 12 19.75C12.4142 19.75 12.75 19.4142 12.75 19H11.25ZM7.5431 10.7672L12.5431 5.51724L11.4569 4.48276L6.4569 9.73276L7.5431 10.7672ZM11.4569 5.51724L16.4569 10.7672L17.5431 9.73276L12.5431 4.48276L11.4569 5.51724ZM11.25 5V19H12.75V5H11.25Z' fill='#000000'></path> </svg></button>" +
                          "<div class='buttonsDivTitle2'> <span id='beklemedeger'></span> </div>" +
                          "</div>" +

                          "<div class=''>" +
                          "<div class='dataBox'><div class='dataBoxTitle'>AKIM</div><div class='dataBoxValue' id='akim'><span id='syscurrent'></span></div></div>" +
                          "<div class='dataBox'><div class='dataBoxTitle'>SICAKLIK</div><div class='dataBoxValue'<span id='systemp'></span></div></div> " +
                          "<div class='dataBox'><div class='dataBoxTitle'>FREKANS</div><div class='dataBoxValue'><span id='sysfrekans'></span></div></div>" +
                          "</div>" +

                          "<div class=''>" +
                          "<div class='dataBox'><div class='dataBoxTitle'>Temp A</div><div class='dataBoxValue' id='akim'><span id='systemp_A'></span></div></div>" +
                          "<div class='dataBox'><div class='dataBoxTitle'>Temp B</div><div class='dataBoxValue'<span id='systemp_B'></span></div></div> " +
                          "<div class='dataBox'><div class='dataBoxTitle'>Temp C</div><div class='dataBoxValue'><span id='systemp_C'></span></div></div>" +
                          "</div>" +

                          "</div></div><br>" +

                          "<div class='form-container'>" +
                          "<h2>Cihaz Bilgileri</h2>" +
                          "<h3>- Wi-Fi Bilgileri -</h3>" +
                          "<p> <strong>Bağlı Ağ:</strong> " + ssid_STA + "</p>" +
                          "<p> <strong>IP Adresi:</strong> " + WiFi.localIP().toString() + "</p>" +
                          "<p> <strong>MAC Adresi:</strong> " + WiFi.macAddress() + "</p>" +
                          "<p> <strong>Host Adı:</strong> " + hostname + "</p>" +

                          "<h3>- Diğer -</h3>" +
                          "<p> <strong>CPU Temp.:</strong> <span id='cpuTemp'></span></p>" +
                          "<p> <strong>Sistem Çalışma Süresi.:</strong> <span id='sysWorkingTime'></span></p>" +
                          "</div>" +
                          "<br>" +

                          "<div class='form-container'>" +
                          "<h2>Ayarlar</h2>" +
                          "<button onclick='document.getElementById(\"loginPopup\").style.display = \"block\";'>Yönetici Ayarları Girişi</button>" +
                          "<p> <em>Made in <strong>Kule Kalıp</strong>. Design by <strong>S. KAYA</strong></em></p>" +
                          "</div>" +

                          "<div id='loginPopup' class='popup'>" +
                          "<span class='close' onclick='document.getElementById(\"loginPopup\").style.display = \"none\";'>&times;</span>" +
                          "<h2>Yönetici Girişi</h2>" +
                          "<form>" +
                          "<label for='username'>Kullanıcı Adı:</label>" +
                          "<input type='text' id='username' name='username' required><br><br>" +
                          "<label for='password'>Şifre:</label>" +
                          "<input type='password' id='password' name='password' required><br><br>" +
                          "<input type='button' value='Giriş Yap' onclick='authenticateUser()'>" +
                          "</form>" +
                          "</div>" +
                          "<div id='advancedSettingsPopup' class='popup' style='display: none;'>" +
                          "<span class='close' onclick='closeAdvancedSettingsPopup()' style='font-size: 28px;'>&times;</span>" +
                          "<h2>Gelişmiş Ayarlar</h2>" +
                          "<h3>- Yazılım Güncelleme -</h3>" +

                          //"<form id='uploadForm' method='POST' action ='/update' enctype='multipart/form-data'>" +
                          //"<input type='file' id='fileInput' name='update'onchange='checkFile()'>" +
                          //"<input type='submit' value='Yazılımı Yükle' class='button' id='uploadButton' disabled>" +
                          //"</form>" +

                          "<form method='POST' action='/update' enctype='multipart/form-data'>" +
                          "<input type='file' name='update'>" +
                          "<input type='submit' value='Yazılımı Yükle' class='button'>" +
                          "</form>" +

                          "<p> <strong>Mevcut Versiyon:</strong> " + VERSIYON + "</p>" +
                          "<button onclick='resetDevice()' class='button'>Fabrika Ayarlarına Dön</button>" +
                          "<h3>- Sistem -</h3>" +
                          "<button onclick='restartDevice()' class='button'>Yeniden Başlat</button>" +
                          "</div>" +

                          "</body></html>";

    return MainPagehtlm;
}

String generateUpdateFailForm(String errorCode)
{

    String UpdateFailPageScript = String("<script> </script>");

    String UpdateFailPagecss = String("<style>") +
                               "body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }" +
                               ".fail-msg { color: red; font-size: 24px; }" +
                               ".button { padding: 10px 20px; font-size: 18px; background-color: #007bff; color: #fff; border: none; border-radius: 5px; cursor: pointer; text-decoration: none; }" +
                               "</style>";

    String UpdateFailPagehtml = String("<!DOCTYPE html<html><head><meta charset='UTF-8'><title>" + UYGULAMA + " Güncelleme Başarısız</title></head><body>") +
                                UpdateFailPageScript +
                                UpdateFailPagecss +
                                "<h1>Güncelleme Başarısız!</h1>" +
                                "<p class='fail-msg'>Hata Kodu: " + errorCode + "</p>" +
                                "<a href='/' class='button'>Ana Sayfa</a>" + // Buton ile ana sayfaya yönlendirme
                                "</body></html>";

    return UpdateFailPagehtml;
}

String generateUpdateSuccessForm()
{

    String UpdateSuccessPageScript = String("<script> </script>");

    String UpdateSuccessPagecss = String("<style>") +
                                  "body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; background-image: url('arka_plan_resmi.png'); background-size: cover; }" +
                                  ".success-msg { color: green; font-size: 24px; }" +
                                  ".button { padding: 10px 20px; font-size: 18px; background-color: #007bff; color: #fff; border: none; border-radius: 5px; cursor: pointer; text-decoration: none; }" +
                                  "</style>";

    String UpdateSuccessPagehtml = String("<!DOCTYPE html<html><head><meta charset='UTF-8'><title>" + UYGULAMA + " Güncelleme Başarılı</title></head><body>") +
                                   UpdateSuccessPageScript +
                                   UpdateSuccessPagecss +
                                   "<h1>Güncelleme Başarılı!</h1>" +
                                   "<p class='success-msg'>Güncelleme başarıyla tamamlandı! Cihaz yeniden başlatılıyor..</p>" +
                                   "<a href='/' class='button'>Ana Sayfa</a>" + // Buton ile ana sayfaya yönlendirme
                                   "</body></html>";
    return UpdateSuccessPagehtml;
}

String generateUpdateInProgressForm()
{

    String UpdateInProgressPageScript = String("<script> </script>");

    String UpdateInProgressPagecss = String("<style>") +
                                     "body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }" +
                                     "</style>";

    String UpdateInProgressPagehtml = String("<!DOCTYPE html<html><head><meta charset='UTF-8'><title>" + UYGULAMA + " Güncelleme İlerliyor</title></head><body>") +
                                      UpdateInProgressPageScript +
                                      UpdateInProgressPagecss +
                                      "<body><h1>Güncelleme İlerliyor</h1><p>Lütfen bekleyiniz.</p>" +
                                      "</body></html>";
    return UpdateInProgressPagehtml;
}
