----------------------------------------------------------------------------------
-- Company:          Montana State University
-- Author/Engineer:	Matthew Handley
--							David Keltgen
-- 
-- Create Date:    	2014-11-25
-- Design Name: 
-- Module Name:    crc - Behavioral 
-- Project Name: 
-- Target Devices: DE2 board
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity crc_control is
	 Port (  clk            : in  STD_LOGIC;  	-- PWM timing is based on the number of clock cycles from clk
				reset          : in  STD_LOGIC;  	-- reset 
				
				-- control register bits
				enable			: in 	STD_LOGIC;		-- enable module
				start				: in 	STD_LOGIC;		-- start calculation
				fifo_empty		: out STD_LOGIC;		-- FIFO empty status flag
				fifo_full		: out STD_LOGIC;		-- FIFO full status flag
				complete			: out STD_LOGIC;		-- calculation complete
				
				vword   			: in STD_LOGIC_VECTOR (15 downto 0); 	-- Read only, Indicates the number of valid words in the FIFO
				dwidth  			: in STD_LOGIC_VECTOR ( 5 downto 0); 	-- Width of a data word
				plen  			: in STD_LOGIC_VECTOR ( 5 downto 0); 	-- Polynomial width
				poly 				: in STD_LOGIC_VECTOR (31 downto 0); 	-- Polynomial coefficients

				FIFO 				: in STD_LOGIC_VECTOR (31 downto 0); 	-- Writes data to the FIFO
				SHIFT 			: in STD_LOGIC_VECTOR (31 downto 0); 	-- Writes to the CRC shift register
				RESULT 			: out STD_LOGIC_VECTOR (31 downto 0) 	-- The CRC calculation result.
	);
end entity;

architecture Behavioral of crc_control is
			
			

begin

	
	
	

end Behavioral;

