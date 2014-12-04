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
use IEEE.numeric_std.ALL;

entity crc_control is
	 Port (  clk            : in  STD_LOGIC;  	-- PWM timing is based on the number of clock cycles from clk
				reset          : in  STD_LOGIC;  	-- reset 
				
				-- control register bits
				enable			: in 	STD_LOGIC;		-- enable module
				start				: in 	STD_LOGIC;		-- start calculation
				fifo_empty		: out STD_LOGIC;		-- FIFO empty status flag
				fifo_full		: out STD_LOGIC;		-- FIFO full status flag
				complete			: out STD_LOGIC;		-- calculation complete
				reset_shift    : in  STD_LOGIC;		-- clears shift register
				shift_change   : in  STD_LOGIC;     -- goes high when shift register changes
				
				vword   			: in STD_LOGIC_VECTOR (15 downto 0); 	-- Read only, Indicates the number of valid words in the FIFO
				dwidth  			: in STD_LOGIC_VECTOR ( 5 downto 0); 	-- Width of a data word
				plen  			: in STD_LOGIC_VECTOR ( 5 downto 0); 	-- Polynomial width
				poly 				: in STD_LOGIC_VECTOR (31 downto 0); 	-- Polynomial coefficients

				--FIFO 				: in STD_LOGIC_VECTOR (31 downto 0); 	-- Writes data to the FIFO
				SHIFT 			: in STD_LOGIC_VECTOR (31 downto 0); 	-- Writes to the CRC shift register
				RESULT 			: out STD_LOGIC_VECTOR (31 downto 0) 	-- The CRC calculation result.
	);
end entity;

architecture Behavioral of crc_control is
	
	signal complete_local		: STD_LOGIC;
	signal data 					: unsigned (8191 downto 0);		-- 1024 bytes
	signal pointer					: integer range 0 to 8191;     			-- keep track of location in data 
	signal dwidth_int 			: integer range 0 to 31;               --
	signal data_mask  			: STD_LOGIC_VECTOR (31 downto 0);        --
	signal dwidth_last  			: STD_LOGIC_VECTOR (5 downto 0);		--
	signal shift_change_last 	: STD_LOGIC;
	signal poly_unsigned 		: unsigned (31 downto 0);

begin

	complete <= complete_local;
	
	-- for debugging
	RESULT <= STD_LOGIC_VECTOR(data(31 downto 0));

	--------------------------------------------------
	-- configures the width of the data if it changes
	--------------------------------------------------
	process(clk, dwidth_int)
	variable dwidth_int_var: 	integer range 0 to 32;
	begin
		if(rising_edge(clk)) then
		
			if(dwidth /= dwidth_last) then
				dwidth_last <= dwidth;
				dwidth_int_var := to_integer(unsigned(dwidth));
			
				case (dwidth_int_var) is
						when 0 => data_mask <=  x"00000000"; 
						when 1 => data_mask <=  x"00000001";
						when 2 => data_mask <=  x"00000003";
						when 3 => data_mask <=  x"00000007";
						when 4 => data_mask <=  x"0000000F";
						when 5 => data_mask <=  x"0000001F";
						when 6 => data_mask <=  x"0000003F";
						when 7 => data_mask <=  x"0000007F";
						when 8 => data_mask <=  x"000000FF";
						when 9 => data_mask <=  x"000001FF";
						when 10 => data_mask <=  x"000003FF";
						when 11 => data_mask <=  x"000007FF";
						when 12 => data_mask <=  x"00000FFF";
						when 13 => data_mask <=  x"00001FFF";
						when 14 => data_mask <=  x"00003FFF";
						when 15 => data_mask <=  x"00007FFF";
						when 16 => data_mask <=  x"0000FFFF";
						when 17 => data_mask <=  x"0001FFFF";
						when 18 => data_mask <=  x"0003FFFF";
						when 19 => data_mask <=  x"0007FFFF";
						when 20 => data_mask <=  x"000FFFFF";
						when 21 => data_mask <=  x"001FFFFF";
						when 22 => data_mask <=  x"003FFFFF";
						when 23 => data_mask <=  x"007FFFFF";
						when 24 => data_mask <=  x"00FFFFFF";
						when 25 => data_mask <=  x"01FFFFFF";
						when 26 => data_mask <=  x"03FFFFFF";
						when 27 => data_mask <=  x"07FFFFFF";
						when 28 => data_mask <=  x"0FFFFFFF";
						when 29 => data_mask <=  x"1FFFFFFF";
						when 30 => data_mask <=  x"3FFFFFFF";
						when 31 => data_mask <=  x"7FFFFFFF";
						when 32 => data_mask <=  x"FFFFFFFF";
						when others => data_mask <= x"FFFFFFFF";
				end case;	
				dwidth_int <= dwidth_int_var;
			end if;
		end if;
	end process;

	--------------------------------------------------
	-- shift the data register over
	--------------------------------------------------
	process(clk)
	
	variable data_local		: unsigned (8191 downto 0);
	
	begin
		if(rising_edge(clk)) then 
		
			if((reset = '0') or (reset_shift = '1')) then
				data <= (others => '0'); 
				pointer <= 0;
				
			else
				if((start = '0') and (enable = '1')) then
					if(shift_change /= shift_change_last) then
						-- udpate shift_change_last and pointer
						shift_change_last <= shift_change;
						pointer <= pointer + dwidth_int;
						
						-- shift the old data to the left and OR in the new data
						data_local := shift_left(data, dwidth_int);
						data_local := data_local OR unsigned(SHIFT and data_mask);
						
						-- update the real data
						data <= data_local;
					end if;
				end if;
			end if;
		end if;
	end process;




	--------------------------------------------------
	-- start the calculation
	--------------------------------------------------
	process(clk)
	begin
		if(rising_edge(clk) and (start = '1') and (complete_local = '0') and (enable = '1')) then
		
		end if;
	end process;	
	
	

end Behavioral;

