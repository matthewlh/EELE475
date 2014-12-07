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
				
				vword   			: out STD_LOGIC_VECTOR (15 downto 0); 	-- Read only, Indicates the number of valid words in the shift register
				dwidth  			: in STD_LOGIC_VECTOR ( 5 downto 0); 	-- Width of a data word
				plen  			: in STD_LOGIC_VECTOR ( 5 downto 0); 	-- Polynomial width
				poly 				: in STD_LOGIC_VECTOR (31 downto 0); 	-- Polynomial coefficients

				--FIFO 				: in STD_LOGIC_VECTOR (31 downto 0); 	-- Writes data to the FIFO
				SHIFT 			: in STD_LOGIC_VECTOR (31 downto 0); 	-- Writes to the CRC shift register
				RESULT 			: out STD_LOGIC_VECTOR (31 downto 0) 	-- The CRC calculation result.
	);
end entity;

architecture Behavioral of crc_control is

	constant shift_reg_size : integer := 256;	-- 32 bytes
	
	signal complete_local		: STD_LOGIC;
	signal data 					: unsigned (shift_reg_size downto 0);		
	signal shift_reg				: unsigned (shift_reg_size downto 0);
	signal vword_int 				: integer range 0 to 65535;
	signal pointer					: integer range 0 to shift_reg_size;     			-- keep track of location in data 
	signal pointer_calc			: integer range 0 to shift_reg_size;     			-- keep track of location in data 
	signal plen_int				: integer range 0 to shift_reg_size;     			-- 
	signal dwidth_int 			: integer range 0 to 31;               --
	signal data_mask  			: STD_LOGIC_VECTOR (31 downto 0);        --
	signal dwidth_last  			: STD_LOGIC_VECTOR (5 downto 0);		--
	signal shift_change_last 	: STD_LOGIC;
	signal poly_uns 				: unsigned (shift_reg_size downto 0);	
	signal RESULT_local 			: STD_LOGIC_VECTOR (31 downto 0); 
	
	-- state machine
	type state_type is ( 
		S_START,
		S_SHIFTING,
		S_DIVIDING, 
		S_DONE
	);
	
	signal current_state		: state_type;
	signal next_state			: state_type;


begin

	complete 	<= complete_local;
	RESULT(30 downto 0)		<= STD_LOGIC_VECTOR(shift_reg(30 downto 0));
	vword  		<= STD_LOGIC_VECTOR(to_unsigned(vword_int, 16));
	
	poly_uns(31 downto 0)	<= unsigned(poly);
	poly_uns(shift_reg_size downto 32) 	<= (others => '0');
	
	plen_int <= to_integer(unsigned(plen));
	
	-- for debugging	
	
--	RESULT(0) <= shift_change;
--	RESULT(1) <= shift_change_last;
--	RESULT(2) <= '1' when ((start = '0') and (enable = '1')) else '0';
--	RESULT(3) <= '1' when ((shift_change /= shift_change_last)) else '0';
--	
--	RESULT(31 downto 4) <= (others => '0');

	--------------------------------------------------
	-- configures the width of the data if it changes
	--------------------------------------------------
	process(clk)
	variable dwidth_int_var: 	integer range 0 to 32;
	begin
		if(clk'event and clk='1') then
		
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
	process(reset, reset_shift, clk, shift_change, start, enable, shift_change_last)
	
		variable shift_reg_local		: unsigned (shift_reg_size downto 0);
	
		begin
		
		if(reset = '1' or reset_shift = '1') then
			pointer <= 0;
			shift_reg <= (others => '0');
			vword_int <= 0;
			
		
		elsif((clk'event) and (clk='1') and 
			(start = '0') and (enable = '1') and 
			(shift_change /= shift_change_last)) then
			
				RESULT(31) <= '1';
				
				-- update shift_change_last and pointer
				shift_change_last <= shift_change;
				pointer <= pointer + dwidth_int;				
				vword_int <= vword_int +1;
				
				-- shift the old data to the left and OR in the new data
				shift_reg_local := shift_left(shift_reg, dwidth_int);
				shift_reg_local := shift_reg_local OR unsigned(SHIFT and data_mask);
				
				-- update the real data
				shift_reg <= shift_reg_local;
			
			
		end if;
		
	
	end process;
	

	


	--------------------------------------------------
	-- STATE_MEMORY 
	--------------------------------------------------
	STATE_MEMORY : process(reset, reset_shift, clk, start, enable, complete_local)
		begin
			if(reset = '1' or reset_shift = '1') then
				current_state 	<= S_START;
				
			elsif((clk'event) and (clk='1') and 
					(start = '1') and (enable = '1') and (complete_local ='0')) then
					
						current_state <= next_state;
			end if;
			
	end process;
	
	--------------------------------------------------
	-- NEXT_STATE_LOGIC 
	--------------------------------------------------
	NEXT_STATE_LOGIC : process(current_state, data, complete_local, pointer_calc)
		begin
			case(current_state) is 
			
				when S_START =>
					if(data(pointer_calc) = '1') then
						next_state <= S_DIVIDING;							
					else
						next_state <= S_SHIFTING;							
					end if;
			
				when S_SHIFTING =>
					if(data(pointer_calc) = '1') then
						next_state <= S_DIVIDING;							
					else
						next_state <= S_SHIFTING;							
					end if;
				
				
			
				when S_DIVIDING =>
					if(complete_local = '1') then
						next_state <= S_DONE;
					else
						next_state <= S_SHIFTING;		
					end if;
				
				when S_DONE =>
					next_state <= S_DONE;
					
				when others =>
					next_state <= S_START;
						
			end case;
				
	end process;	
	
	
	--------------------------------------------------
	-- OUTPUT_LOGIC 
	--------------------------------------------------
	OUTPUT_LOGIC : process(current_state)
	
		begin
			
			case(current_state) is 
			
				when S_START =>
					-- latch and shift shift_reg into data, so that we have room for the remainder (RESULT)
					pointer_calc <= pointer + dwidth_int;		
					data <= shift_left(shift_reg, dwidth_int);
			
				when S_SHIFTING =>
					-- decrement pointer to 'shift' the polynomial to the right					
					pointer_calc <= pointer_calc -1;		

					if(pointer_calc <= dwidth_int) then
						complete_local <= '1';
					end if;	
					
			
				when S_DIVIDING =>		
					-- XOR the polynomial with the data, aligning the MSB of the poly with data(pointer)
					data <= data XOR (shift_left(poly_uns, (pointer_calc - plen_int)));
				
				when S_DONE =>
					complete_local <= '1';
					
				when others => 
						
			end case;
			
	end process;

end Behavioral;




					
						