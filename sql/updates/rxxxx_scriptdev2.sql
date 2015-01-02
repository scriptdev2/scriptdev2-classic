
DELETE FROM `script_waypoint` WHERE `entry`='14353';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
('14353', '0', '728.9432', '483.2973', '28.18182', '0', 'Mizzle the Crafty'),
('14353', '1', '768.2385', '482.2147', '29.74962', '0', 'Mizzle the Crafty'),
('14353', '2', '816.5302', '482.3017', '37.31819', '0', 'Mizzle the Crafty');

DELETE FROM `gossip_texts` WHERE  `entry` IN ('-3509002', '-3509003', '-3509004', '-3509005');
INSERT INTO `gossip_texts` (`entry`, `content_default`, `comment`) VALUES
('-3509002', 'I\'m the new king?  What are you talking about?', 'Mizzle the Crafty'),
('-3509003', 'It\'s good to be the king!  Now, let\'s get back to what you were talking about before...', 'Mizzle the Crafty'),
('-3509004', 'Henchmen?  Tribute?', 'Mizzle the Crafty'),
('-3509005', 'Well then... show me the tribute!', 'Mizzle the Crafty');

DELETE FROM `script_texts` WHERE `entry` IN ('-1999925', '-1999926', '-1999927');
INSERT INTO `script_texts` (`entry`, `content_default`, `type`, `comment`) VALUES
('-1999925', 'OH NOES!  Da king is dead!  Uh... hail to da new king!  Yeah!', '1', 'Mizzle the Crafty'),
('-1999926', 'Yar, he\'s dead all right.  That makes you da new king... well, all of you!  Gordok is yours now, boss!  You should talk to me so you can learn everything there is about being da king!  I was... is his assistant!  Yeah, that\'s why I\'m called da crafty one!', '0', 'Mizzle the Crafty'),
('-1999927', 'The king is dead - OH NOES!  Summon Mizzle da Crafty!  He knows what to do next!', '1', 'Cho\'Rush the Observer');
