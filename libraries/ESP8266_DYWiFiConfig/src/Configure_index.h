
const char PAGE_IndexPage[] PROGMEM = R"=====(
<!DOCTYPE html><style>fieldset{padding-top:10px;border:1px solid #666;border-radius:8px}legend{float:left;margin-top:-20px}legend{padding:1px 1px;background:#fff}legend+*{clear:both}.button{background-color:#4CAF50;border:none;color:#fff;padding:5px 10px;text-align:center;text-decoration:none;display:inline-block;font-size:16px;overflow:visible;text-transform:none;-webkit-appearance:button;cursor:pointer;button::-moz-focus-inner}.button:hover,focus{color:#fff;background-color:#3c763d;border-color:#3c763d}</style><div>Wifi Direct IP:{A-IP}</div><p><fieldset><legend>Wifi Setting</legend><p>SSID Name:{S-SSID}<p>SSID Password:{S-PWD}<p>Status:{S-STATUS}<form action=reconnect id=form-reconnect name=form-reconnect><input type=submit value=Reconnect class=button style=font-size:110%> <input name=reconnect type=hidden value=1></form><br><fieldset><legend>IP</legend><p>DHCP:{S-DHCP}<p>IP:{S-IP}<p>GW:{S-GW}<p>DNS:{S-DNS}</fieldset></fieldset><p><p><form action=setting id=form-setting name=form-setting onsubmit="return checkAllField(this)"><fieldset><legend>Change Setting</legend><p></p>SSID<select id=SSIDFastSelection name=ssids onchange='ValueFillTo(this.id,"SSIDName")'style=width:90%;font-size:110%><option value=*-*>===SELECT===</option>{C-SSIDOPT}</select><p><p><label for=SSIDName>SSID Name</label><input name=ssid id=SSIDName maxlength=32 style=width:80%;font-size:110%><p><label for=SSIDPassword>SSID Password</label><input name=pass id=SSIDPassowrd maxlength=32 style=width:80%;font-size:110%><p><label for=dhcpAuto>Auto</label><input name=dhcpAuto id=dhcpAuto onclick='showBlock("ManualIP",!1)'type=radio value=1 checked><label for=dhcpAuto>Manual</label><input name=dhcpAuto id=dhcpAuto onclick='showBlock("ManualIP",!0)'type=radio value=0><div id=ManualIP><fieldset><legend>Setting</legend><p><table border=0px cellpadding=1px cellspacing=1px><tr><td>IP<td><input name=ip1 id=ip1 maxlength=3>. <input name=ip2 id=ip2 maxlength=3>. <input name=ip3 id=ip3 maxlength=3>. <input name=ip4 id=ip4 maxlength=3><tr><td>Gateway<td><input name=gw1 id=gw1 maxlength=3>. <input name=gw2 id=gw2 maxlength=3>. <input name=gw3 id=gw3 maxlength=3>. <input name=ip4 id=gw4 maxlength=3><tr><td>Netmask<td><input name=sn1 id=sn1 maxlength=3>. <input name=sn2 id=sn2 maxlength=3>. <input name=sn3 id=sn3 maxlength=3>. <input name=sn4 id=sn4 maxlength=3><tr><td>DNS<td><input name=dns1 id=dns1 maxlength=3>. <input name=dns2 id=dns2 maxlength=3>. <input name=dns3 id=dns3 maxlength=3>. <input name=dns4 id=dns4 maxlength=3></table></fieldset></div><input type=submit value=Save class=button></fieldset></form><script>function checkVaildRange(e,a,t){var n=document.getElementById(e),c=n.value;return c<a||c>t?(alert("Range is:"+a+"~"+t),n.style.border="thick solid #0000FF",setTimeout(function(){n.focus()},1),1):(n.style.border="",0)}function setIDValue(e,a){var t=document.getElementById(e);t.value=a}function checkVaildText(e,a,t){var n=document.getElementById(e),c=n.value;return""==c?(t&&t(a),n.style.border="thick solid #0000FF",setTimeout(function(){n.focus()},1),1):(n.style.border="",0)}function ValueFillTo(e,a){var t=document.getElementById("SSIDName"),n=document.getElementById(e).value;"*-*"!=n&&(t.value=n,t.focus())}function showBlock(e,a){a?(document.getElementById(e).style.display="",dhcpAuto=0):(dhcpAuto=1,document.getElementById(e).style.display="none")}function checkAllField(e){return 1!=checkVaildText("SSIDName","SSID Name is empty",!0)&&(1==checkVaildText("SSIDPassowrd","SSID Password is empty",!1)&&setIDValue("SSIDPassowrd",""),console.log("dhcpAuto:"+dhcpAuto),1==dhcpAuto?(setIDValue("ip1","0"),setIDValue("ip2","0"),setIDValue("ip3","0"),setIDValue("ip4","0"),setIDValue("gw1","0"),setIDValue("gw2","0"),setIDValue("gw3","0"),setIDValue("gw4","0"),setIDValue("sn1","0"),setIDValue("sn2","0"),setIDValue("sn3","0"),setIDValue("sn4","0"),setIDValue("dns1","0"),setIDValue("dns2","0"),setIDValue("dns3","0"),setIDValue("dns4","0"),!0):1!=checkVaildRange("ip1",1,255)&&(1!=checkVaildRange("ip2",1,255)&&(1!=checkVaildRange("ip3",1,255)&&(1!=checkVaildRange("ip4",1,255)&&(1!=checkVaildRange("gw1",1,255)&&(1!=checkVaildRange("gw2",1,255)&&(1!=checkVaildRange("gw3",1,255)&&(1!=checkVaildRange("gw4",1,255)&&(1!=checkVaildRange("sn1",0,255)&&(1!=checkVaildRange("sn2",0,255)&&(1!=checkVaildRange("sn3",0,255)&&(1!=checkVaildRange("sn4",0,255)&&(1!=checkVaildRange("dns1",1,255)&&(1!=checkVaildRange("dns2",1,255)&&(1!=checkVaildRange("dns3",1,255)&&1!=checkVaildRange("dns4",1,255))))))))))))))))}var dhcpAuto;!function(){showBlock("ManualIP",!1)}()</script>
)=====";
const char PAGE_404Page[] PROGMEM = R"=====(
<!DOCTYPE html><style>div.blue{border-left:6px solid #0cf;background-color:#fff}</style><div class=blue>404 not found</div>
)=====";
