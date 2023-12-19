/*
 Navicat Premium Data Transfer

 Source Server         : 192.168.1.133
 Source Server Type    : MySQL
 Source Server Version : 50724 (5.7.24)
 Source Host           : 192.168.1.133:3308
 Source Schema         : global_auth

 Target Server Type    : MySQL
 Target Server Version : 50724 (5.7.24)
 File Encoding         : 65001

 Date: 21/11/2023 12:11:38
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for t_auth_info
-- ----------------------------
DROP TABLE IF EXISTS `t_user_log_collector_info`;
--- 日志收集权限
CREATE TABLE `t_user_log_collector_info`  (
  `id` int(10)   NOT NULL AUTO_INCREMENT,
  `client_type` int(10)      DEFAULT 0 COMMENT '客户端类型  0 未知客户端 1: 3D  2: Rte',
  `log_level` int(10)      DEFAULT 0   COMMENT '日志级别',
  `address`   varchar(1024) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL  COMMENT '客户端ip地址',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `address`(`address`) USING BTREE
) ENGINE = InnoDB  DEFAULT CHARSET=utf8;





DROP TABLE IF EXISTS `t_log_collector_info`;
--- 日志收集权限
CREATE TABLE `t_log_collector_info`  (
  `id` int(10)   NOT NULL AUTO_INCREMENT,
  `client_type` int(10)      DEFAULT 0 COMMENT '客户端类型  0 未知客户端 1: 3D  2: Rte',
    `address`   varchar(1024) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL  COMMENT '客户端ip地址',
	`timestamp` int(10) NOT NULL  COMMENT '时间戳',
  `log_file_name` varchar(1024) CHARACTER SET utf8 COLLATE utf8_general_ci     DEFAULT NULL   COMMENT '日志文件名称',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `client_type`(`client_type`) USING BTREE,
  INDEX `address`(`address`) USING BTREE,
  INDEX `timestamp`(`timestamp`) USING BTREE
) ENGINE = InnoDB  DEFAULT CHARSET=utf8;


---------------
-- CREATE TABLE t_employees (
--  
-- id INT NOT NULL,
--  
-- fname VARCHAR(30),  
--  
-- store_id INT NOT NULL
--  
-- ) 
-- PARTITION BY RANGE (store_id) (
--  
-- PARTITION p0 VALUES LESS THAN (6),
--  
-- PARTITION p1 VALUES LESS THAN (11),
--  
-- PARTITION p2 VALUES LESS THAN (16),
--  
-- PARTITION p3 VALUES LESS THAN MAXVALUE
--  
-- );
-------------------------



-- ----------------------------
-- Table structure for t_version
-- ----------------------------
DROP TABLE IF EXISTS `t_version`;
CREATE TABLE `t_version`  (
  `version` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`version`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Fixed;

SET FOREIGN_KEY_CHECKS = 1;
