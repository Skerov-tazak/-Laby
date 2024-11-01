call plug#begin('~/local/share/nvim/plugged')

Plug 'https://github.com/preservim/nerdtree'
Plug 'neoclide/coc.nvim', {'branch': 'release'}
Plug 'https://github.com/vim-airline/vim-airline'
Plug 'https://github.com/vim-airline/vim-airline-themes'
Plug 'https://github.com/ellisonleao/gruvbox.nvim'
Plug 'https://github.com/jiangmiao/auto-pairs'
Plug 'nvim-treesitter/nvim-treesitter', {'do': ':TSUpdate'}
call plug#end()

" Terminal Function
let g:term_buf = 0
let g:term_win = 0
function! TermToggle(height)
    if win_gotoid(g:term_win)
        hide
    else
        botright new
        exec "resize " . a:height
        try
            exec "buffer " . g:term_buf
        catch
            call termopen($SHELL, {"detach": 0})
            let g:term_buf = bufnr("")
            set nonumber
            set norelativenumber
            set signcolumn=no
        endtry
        startinsert!
        let g:term_win = win_getid()
    endif
endfunction

" Toggle terminal on/off (neovim)
nnoremap <F7> :call TermToggle(14)<CR>
inoremap <F7> <Esc>:call TermToggle(14)<CR>
tnoremap <F7> <C-\><C-n>:call TermToggle(14)<CR>

" Terminal go back to normal mode
tnoremap <Esc> <C-\><C-n>
tnoremap :q! <C-\><C-n>:q!<CR>

nmap <c-k> <c-w>k 
nmap <c-j> <c-w>j
nmap <c-h> <c-w>h
nmap <c-l> <c-w>l

:set foldmethod=marker
:set shiftwidth=4
:set tabstop=4
:set foldmarker=//{,//}
:set nowrap
:set foldlevel=1
:colorscheme gruvbox
:set number
let g:airline_theme='deus'
nmap <F8> :NERDTreeToggle<CR>
autocmd BufRead * TSBufEnable highlight
autocmd VimEnter * TSBufEnable highlight
inoremap <expr> <Tab> coc#pum#visible() ? coc#pum#next(1) : "\<Tab>"
inoremap <expr> <S-Tab> coc#pum#visible() ? coc#pum#prev(1) : "\<S-Tab>"
inoremap <expr> <cr> coc#pum#visible() ? coc#pum#confirm() : "\<CR>"
