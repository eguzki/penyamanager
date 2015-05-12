INSERT INTO `member` (idmember, name, surname, image, lastmodified, reg_date, active, isAdmin, bank_account) VALUES (1,'Eguzki','Astiz Lezaun','mypicture.png','2014-12-01 00:00:00','2014-12-01 00:00:00',1, 0, "123456789"),(2,'Urko','Usunariz Fernandez','mypicture2.png','2014-12-01 00:00:00','2014-12-01 00:00:00',1, 0, "123456789");
INSERT INTO `account` VALUES (1,1,76.54,'2014-12-01 00:00:00',76.54,'deposit',1),(2,1,-54.50,'2014-12-01 00:00:01',22.04,'invoice id: 1',0),(3,2,20.00,'2014-12-01 00:00:01',20.00,'deposit',1);
INSERT INTO `product_family` VALUES (1,'refreshments','refresh.jpg',1,'2014-12-14 13:31:19'),(2,'liquors','liquors.jpg',1,'2014-12-14 13:34:23'),(3,'beers','beers.jpg',1,'2014-12-14 13:34:23'),(4,'wines','wines.jpg',1,'2014-12-14 13:34:23'),(5,'patxaranak','patxaranak.jpg',1,'2014-12-14 13:34:23');
INSERT INTO `product_item` VALUES (1,'water','water.jpg',1,'2014-12-14 13:38:57',1,1.00),(2,'coke','coke.jpg',1,'2014-12-14 13:38:57',1,2.00),(3,'licor43','licor43.jpg',1,'2014-12-14 13:38:57',2,3.00),(4,'orujo','orujo.jpg',1,'2014-12-14 13:38:57',2,2.50),(5,'franziskaner','franziskaner.jpg',1,'2014-12-14 13:38:57',3,3.50),(6,'naparbier','naparbier.jpg',1,'2014-12-14 13:38:57',3,1.00);
INSERT INTO `invoice` VALUES (1,1,'2014-12-23 17:11:52',-54.50,1),(2,0,'2014-12-23 17:11:52',-3.50,2);
INSERT INTO `inv_prod` VALUES (1,1,10),(1,2,10),(1,5,7),(2,5,1);
INSERT INTO `deposit` VALUES (1,1,'2014-12-01 00:00:00',76.54,"deposit",1);
INSERT INTO `lunchtables` (idtable, name, guestnum) VALUES ('1', 'mahaia1', '8');
INSERT INTO `lunchtables` (idtable, name, guestnum) VALUES ('2', 'mahaia2', '8');
