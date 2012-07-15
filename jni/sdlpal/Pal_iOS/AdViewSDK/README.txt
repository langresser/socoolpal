AdNetworks
==========

版本说明
========
Google Admob SDK	--	6.0.4
多盟					--	3.0.0
VPON SDK			--	3.2.4
LMMOB SDK			--	2.0
Millennial Media	--	4.5.5a
友盟					--	1.1.4
Youmi				--	4.0
SmartMad			--	2.0.3
微云					--	3.0
易传媒				--	2.5.1
艾徳思奇				--	2.3.0
Wooboo				--	2.2.1
Adwo				--	2.5.2
MobWin 聚赢			--	1.3
WQ 帷千				--	2.0.4
AirAD 				--	1.3.1
Ader				--	1.0.2
Baidu				--  2.0

符号冲突
========
Wooboo / LMMOB / WinAd / MobWin : Reachability.o 冲突
AdFracta 与 Domob 的 getMacAddress 冲突
MobWin 与 IZP 的 InitAddresses 冲突
MobWin 与 LMMOB 的 Reachability.o 冲突
Domob 与 SmartMad 的 DMTimer.o 冲突
Ader 与 Youmi 的 AdWebView.o 有冲突


一些平台对于xcode版本或者sdk版本有限制， 不满足需求请不链接该平台库
========
AirAD仅支持xcode4.2, ios4.0以上。
Admob要求xcode4.2以上。

其他说明
========
有米4.0在模拟器点击会崩溃，但真机正常。

开源库使用
========
JSONKit  		-- 友盟使用
SBJson   		-- AdView及一些平台
TouchJSON		-- AdView及一些平台
ASIHTTPRequest	-- VPON使用
SCGIFImageView	-- AdView使用